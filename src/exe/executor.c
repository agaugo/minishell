/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   executor.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: trstn4 <trstn4@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/08/21 19:24:57 by trstn4        #+#    #+#                 */
/*   Updated: 2023/12/09 22:32:58 by trstn4        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	set_command_path(char **allpath, token_t *current)
{
	char	*fullpath;
	char	*temp;
	int		i = 0;

    int found = 0;
    while (allpath[i])
	{
		temp = ft_strjoin(allpath[i], "/");
		fullpath = ft_strjoin(temp, current->value);
		free(temp);
        if (access(fullpath, X_OK) != -1)
        {
            found = 1;
			free(current->value);
			current->value = fullpath;
			break ;
		}
		free(fullpath);
		i++;
	}
    return found; // Return 1 if found, 0 otherwise
}

int file_exists_and_executable(const char *path)
{
    struct stat statbuf;

    // Use stat to get information about the file
    if (stat(path, &statbuf) != 0)
    {
        return 0; // File doesn't exist or stat failed
    }

    // Check if the file is a regular file and if it's executable
    return S_ISREG(statbuf.st_mode) && (access(path, X_OK) == 0);
}

int	is_builtin_command(char *command)
{
    if (command == NULL)
        return (1);
	const char *builtins[] = {"echo", "cd", "export", "unset", "env", "exit",
		"pwd", NULL};
	for (int i = 0; builtins[i] != NULL; i++)
	{
		if (ft_strcmp(command, builtins[i]) == 0)
		{
			return (1);
		}
	}
	return (0);
}

int is_directory(const char *path)
{
    struct stat statbuf;
    if (stat(path, &statbuf) != 0)
    {
        return 0; // Cannot access path, assume not a directory
    }
    return S_ISDIR(statbuf.st_mode);
}

void	resolve_command_paths(data_t *data)
{
	token_t	*current;
	char	**allpath;
	char	*path;
	int		is_command;

	current = data->tokens;
	path = ft_getenv(data->envp, "PATH");
	is_command = 1;
	if (!path)
	{
		return ;
	}
	allpath = ft_split(path, ':');
	while (current)
	{
		// Check if it's a command (not an argument) and not a built-in command
		if (current->type == T_WORD && is_command
			&& !is_builtin_command(current->value))
		{
            if (strchr(current->value, '/') != NULL)
            {
                if (is_directory(current->value))
                {
                    data->last_exit_code = 126; // Typical exit code for "is a directory"
                    current->status = 126;
                }    
            }
            else
            {
             	if (!set_command_path(allpath, current))
                {
                    data->last_exit_code = 127; // Typical exit code for command not found
                    current->status = 127;
                }   
            }
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

char	**ms_get_full_args(token_t *start_token, token_t *end_token)
{
	int		arg_count;
	char	**args;
	token_t	*current;

	current = start_token;
	// Count arguments until end_token or a redirection token is encountered
	arg_count = 0;
	while (current != end_token && current->type != T_REDIRECT_OUT
		&& current->type != T_APPEND_OUT && current->type != T_REDIRECT_IN)
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
		if (current->type == T_REDIRECT_OUT)
		{
			break ;
		}
		args[i] = ft_strdup(current->value);
		current = current->next;
	}
	args[arg_count] = NULL;
	return (args);
}

void	ms_run_builtin(data_t *data, char **args, token_t *current)
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

void	execute_builtin_command_in_pipe(char **args, data_t *data, int fd_write,
		token_t *current)
{
	dup2(fd_write, STDOUT_FILENO);
	close(fd_write);
	ms_run_builtin(data, args, current);
	exit(EXIT_SUCCESS);
}
void execute_builtin_command(char **args, data_t *data, int fd_write, token_t *current, int is_pipe)
{
    if (fd_write != STDOUT_FILENO)
    {
        dup2(fd_write, STDOUT_FILENO);
        close(fd_write);
    }
    ms_run_builtin(data, args, current);
    if (is_pipe)

        exit(EXIT_SUCCESS);
}

int setup_redirection(token_t *tokens)
{
    token_t *current;
    int fd;
    int flags;

    current = tokens;
    while (current != NULL) {
        if (current->type == T_REDIRECT_IN) {
            if (access(current->next->value, F_OK) == -1) {
                fprintf(stderr, "bash: %s: No such file or directory\n", current->next->value);
                return -1; // Return error code for missing input file
            }
            flags = O_RDONLY;
            fd = open(current->next->value, flags);
            if (fd == -1) {
                perror("open");
                return -1;
            }
            dup2(fd, STDIN_FILENO);
            close(fd);
        } else if (current->type == T_REDIRECT_OUT || current->type == T_APPEND_OUT) {
            flags = (current->type == T_APPEND_OUT) ? (O_WRONLY | O_CREAT | O_APPEND) : (O_WRONLY | O_CREAT | O_TRUNC);
            fd = open(current->next->value, flags, 0666);
            if (fd == -1) {
                perror("open");
                return -1;
            }
            dup2(fd, STDOUT_FILENO);
            close(fd);
        }
        current = current->next;
    }
    return 0; // Success
}


void ms_execute_commands(data_t *data) {
    pid_t pid;
    token_t *current;
    token_t *next_command;
    int status;
    char **args;

    int fds[2];
    int in_fd = 0; // Initial input file descriptor

    current = data->tokens;
    while (current != NULL) {
        next_command = current;

        // Determine if the current command is part of a pipe
        int is_pipe = 0;
        int is_redirect = 0;
        while (next_command != NULL) {
            if (next_command->type == T_PIPE) {
                is_pipe = 1;
                break;
            }
            if (next_command->type == T_REDIRECT_OUT || next_command->type == T_APPEND_OUT ||
                next_command->type == T_REDIRECT_IN) {
                is_redirect = 1;
            }
            next_command = next_command->next;
        }

        args = ms_get_full_args(current, next_command);

        // Handle built-in commands differently when they are part of a pipeline
        if (is_builtin_command(args[0]) && !is_pipe && !is_redirect) {
            ms_run_builtin(data, args, current);
        } else {
            // Set up pipe if needed
            if (is_pipe) {
                pipe(fds);
            }

            pid = fork();
            if (pid == 0) { // Child process
                if (in_fd != 0) {
                    dup2(in_fd, STDIN_FILENO);
                    close(in_fd);
                }
                if (is_pipe) {
                    dup2(fds[1], STDOUT_FILENO);
                    close(fds[0]);
                    close(fds[1]);
                }

                // Setup redirections
                if (is_redirect) {
                    if (setup_redirection(current) == -1) {
                        exit(EXIT_FAILURE); 
                    }
                }

                // Execute command
                if (is_builtin_command(args[0])) {
                    ms_run_builtin(data, args, current);
                    exit(EXIT_SUCCESS);
                } else {
                    // Execute external command
                    if (current->status == 126)
                    {
                        fprintf(stderr, "%s: is a directory\n", current->value);
                        data->last_exit_code = 126;
                        exit(126);
                    }

                    if (current->status == 127)
                    {
                        fprintf(stderr, "%s: command not found\n", current->value);
                        data->last_exit_code = 127;
                        exit(127);
                    }
                    
                    execve(args[0], args, data->envp);

                    // If execve returns, it means there was an error
                    if (errno == ENOENT)
                    {
                        // No such file or directory
                        perror("execve");
                        exit(127);
                    }
                    else if (errno == EACCES)
                    {
                        // Permission denied
                        perror("execve");
                        exit(126);
                    }
                    else
                    {
                        // Other errors
                        perror("execve");
                        exit(EXIT_FAILURE);
                    }
                }
            } else if (pid < 0) {
                perror("fork");
                exit(EXIT_FAILURE);
            }

            // Parent process handling
            if (in_fd != 0) {
                close(in_fd);
            }
            if (is_pipe) {
                close(fds[1]);
                in_fd = fds[0];
            } else {
                in_fd = 0;
            }

            waitpid(pid, &status, 0); // Wait for the child process to finish
            data->last_exit_code = WEXITSTATUS(status);
        }

        current = next_command ? next_command->next : NULL;
    }
}
