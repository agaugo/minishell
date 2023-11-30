/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   executor.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: trstn4 <trstn4@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/08/21 19:24:57 by trstn4        #+#    #+#                 */
/*   Updated: 2023/11/30 18:11:46 by trstn4        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void set_command_path(char **allpath, token_t *current)
{
    char *fullpath;
    char *temp;
    int i;

    i = 0;
    while (allpath[i])
    {
        temp = ft_strjoin(allpath[i], "/");
        fullpath = ft_strjoin(temp, current->value);
        free(temp);
        if (access(fullpath, X_OK) != -1)
        {
            free(current->value);
            current->value = fullpath;
            break;
        }
        free(fullpath);
        i++;
    }
}

int is_builtin_command(char *command)
{
    const char *builtins[] = {"echo", "cd", "export", "unset", "env", "exit", "pwd", NULL};
    for (int i = 0; builtins[i] != NULL; i++)
    {
        if (ft_strcmp(command, builtins[i]) == 0)
		{
			return 1;
		}
    }
    return 0;
}

void resolve_command_paths(data_t *data)
{
    token_t *current = data->tokens;
    char **allpath;
    char *path = ft_getenv(data->envp, "PATH");
    int is_command = 1;

    if (!path)
    {
        perror("PATH not set");
        return;
    }

    allpath = ft_split(path, ':');

    while (current)
    {
        // Check if it's a command (not an argument) and not a built-in command
        if (current->type == T_WORD && is_command && !is_builtin_command(current->value))
        {
            set_command_path(allpath, current);
        }

        // Reset is_command for the next command in the pipeline
        if (current->type == T_PIPE)
            is_command = 1;
        else
            is_command = 0;

        current = current->next;
    }

    ms_free_2d_array(allpath);
}

// static int count_args(token_t *start, token_t *end)
// {
//     int count;

//     count = 0;
//     while (start != end)
//     {
//         count++;
//         start = start->next;
//     }
//     return (count);
// }

// static void fill_args_array(char **args, token_t *start, int arg_count)
// {
//     int i;

//     i = 0;
//     while (i < arg_count)
//     {
//         args[i] = ft_strdup(start->value);
//         start = start->next;
//         i++;
//     }
//     args[arg_count] = NULL;
// }

void setup_output_redirection(token_t *tokens) {
    token_t *current = tokens;

    while (current != NULL) {
        if (current->type == T_REDIRECT_OUT) {
            // Truncate and write to the file
            int fd = open(current->next->value, O_WRONLY | O_CREAT | O_TRUNC, 0666);
            if (fd == -1) {
                perror("open");
                exit(EXIT_FAILURE);
            }
            dup2(fd, STDOUT_FILENO);
            close(fd);
        }
        else if (current->type == T_APPEND_OUT) {
            // Append to the file
            int fd = open(current->next->value, O_WRONLY | O_CREAT | O_APPEND, 0666);
            if (fd == -1) {
                perror("open");
                exit(EXIT_FAILURE);
            }
            dup2(fd, STDOUT_FILENO);
            close(fd);
        }
        current = current->next;
    }
}

char **ms_get_full_args(token_t *start_token, token_t *end_token)
{
    int     arg_count;
    char    **args;
    token_t *current = start_token;

    // Count arguments until end_token or a redirection token is encountered
    arg_count = 0;
    while (current != end_token && current->type != T_REDIRECT_OUT && current->type != T_APPEND_OUT)
    {
        arg_count++;
        current = current->next;
    }

    args = (char **)malloc((arg_count + 1) * sizeof(char *));
    if (!args)
    {
        perror("Failed to allocate memory for arguments");
        return (NULL);
    }

    // Fill the array with arguments until a redirection token is encountered
    current = start_token;
    for (int i = 0; i < arg_count; i++)
    {
        if (current->type == T_REDIRECT_OUT) {
            break;
        }
        args[i] = ft_strdup(current->value);
        current = current->next;
    }
    args[arg_count] = NULL;

    return (args);
}

// static void execute_child_process(char **args, int fds[2], int in_fd, token_t *next_command, data_t *data)
// {
//     if (in_fd != 0)
//     {
//         dup2(in_fd, 0);
//         close(in_fd);
//     }
//     if (next_command != NULL)
//     {
//         dup2(fds[1], 1);
//         close(fds[0]);
//         close(fds[1]);
//     }
//     execve(args[0], args, data->envp);
//     perror("execve");
//     exit(EXIT_FAILURE);
// }

void ms_run_builtin(data_t *data, char **args, token_t *current)
{
    if (ft_strcmp(args[0], "export") == 0)
        ms_export_command(data, current);
    else if (ft_strcmp(args[0], "unset") == 0)
        ms_unset_command(data, current);
    else if (ft_strcmp(args[0], "env") == 0)
        ms_print_env_variables(data);
    else if (ft_strcmp(args[0], "pwd") == 0)
        ms_pwd_command(data);
    else if (ft_strcmp(args[0], "cd") == 0)
        ms_cd_command(data, current);
    else if (ft_strcmp(args[0], "echo") == 0)
        ms_echo_command(data, current);
    else if (ft_strcmp(args[0], "exit") == 0)
        ms_exit_shell(data, current->next);
}

void execute_builtin_command_in_pipe(char **args, data_t *data, int fd_write, token_t *current)
{
    dup2(fd_write, STDOUT_FILENO);
    close(fd_write);
	
	ms_run_builtin(data, args, current);
	
    exit(EXIT_SUCCESS);
}

void execute_builtin_command(char **args, data_t *data, int fd_write, token_t *current)
{
    // Redirect standard output to the write end of the pipe if necessary
    if (fd_write != STDOUT_FILENO)
    {
        dup2(fd_write, STDOUT_FILENO);
        close(fd_write);
    }

	ms_run_builtin(data, args, current);
	
    // Restore STDOUT if changed
    if (fd_write != STDOUT_FILENO)
    {
        dup2(STDOUT_FILENO, fd_write);
    }

    // If part of a pipeline, exit the child process
    if (fd_write != STDOUT_FILENO)
    {
        exit(EXIT_SUCCESS);
    }
}

void ms_execute_commands(data_t *data)
{
    int fds[2], in_fd = 0;
    pid_t pid;
    token_t *current = data->tokens;
    token_t *next_command;
    int status;

    while (current != NULL)
    {
        char **args;
        next_command = current;
        while (next_command != NULL && next_command->type != T_PIPE)
            next_command = next_command->next;
        args = ms_get_full_args(current, next_command);

        setup_output_redirection(current);

        if (next_command != NULL)
            pipe(fds);

        // Execute built-in commands directly if not part of a pipeline
        if (is_builtin_command(args[0]) && next_command == NULL)
        {
            ms_run_builtin(data, args, current);
        }
        else
        {
            // Handle external commands or built-ins as part of a pipeline
            pid = fork();
            if (pid == 0) // Child process
            {
                if (in_fd != 0)
                {
                    dup2(in_fd, 0);
                    close(in_fd);
                }
                if (next_command != NULL)
                {
                    dup2(fds[1], 1);
                    close(fds[0]);
                    close(fds[1]);
                }
                if (is_builtin_command(args[0]))
                {
                    // Execute the built-in command in the child process
                    ms_run_builtin(data, args, current);
                    exit(EXIT_SUCCESS);
                }
                else
                {
                    // Execute external command
                    execve(args[0], args, data->envp);
                    perror("execve");
                    exit(EXIT_FAILURE);
                }
            }
            else if (pid < 0)
            {
                perror("fork");
                exit(EXIT_FAILURE);
            }

            // Parent process
            if (in_fd != 0)
                close(in_fd);
            if (next_command != NULL)
            {
                close(fds[1]);
                in_fd = fds[0];
            }
            else
                in_fd = 0;

            waitpid(pid, &status, 0); // Wait for the child process to finish
            data->last_exit_code = WEXITSTATUS(status);
        }

        ms_free_2d_array(args); // Assuming this function frees the args array

        dup2(STDOUT_FILENO, 1);

        if (next_command != NULL)
            current = next_command->next;
        else
            current = NULL;
    }
}
