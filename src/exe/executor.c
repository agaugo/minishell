/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   executor.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: trstn4 <trstn4@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/08/21 19:24:57 by trstn4        #+#    #+#                 */
/*   Updated: 2023/11/27 12:36:40 by trstn4        ########   odam.nl         */
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

void resolve_command_paths(data_t *data)
{
    token_t *current;
    char **allpath;
    char *path;
    int is_command;

    current = data->tokens;
    path = ft_getenv(data->envp, "PATH");
    if (!path)
    {
        perror("PATH not set");
        return;
    }
    allpath = ft_split(path, ':');
    is_command = 1;
    while (current)
    {
        if (current->type == T_WORD && is_command)
            set_command_path(allpath, current);
        if (current->type == T_PIPE)
            is_command = 1;
        else
            is_command = 0;
        current = current->next;
    }
    ms_free_2d_array(allpath);
}

static int count_args(token_t *start, token_t *end)
{
    int count;

    count = 0;
    while (start != end)
    {
        count++;
        start = start->next;
    }
    return (count);
}

static void fill_args_array(char **args, token_t *start, int arg_count)
{
    int i;

    i = 0;
    while (i < arg_count)
    {
        args[i] = ft_strdup(start->value);
        start = start->next;
        i++;
    }
    args[arg_count] = NULL;
}

char **ms_get_full_args(token_t *start_token, token_t *end_token)
{
    int     arg_count;
    char    **args;

    arg_count = count_args(start_token, end_token);
    args = (char **)malloc((arg_count + 1) * sizeof(char *));
    if (!args)
    {
        perror("Failed to allocate memory for arguments");
        return (NULL);
    }
    fill_args_array(args, start_token, arg_count);
    return (args);
}

static void execute_child_process(char **args, int fds[2], int in_fd, token_t *next_command, data_t *data)
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
    execve(args[0], args, data->envp);
    perror("execve");
    exit(EXIT_FAILURE);
}

static void handle_parent_process(int fds[2], int *in_fd, token_t *next_command, char **args, data_t *data)
{
    int status;

    if (*in_fd != 0)
        close(*in_fd);
    if (next_command != NULL)
    {
        close(fds[1]);
        *in_fd = fds[0];
    }
    else
        *in_fd = 0;
    ms_free_2d_array(args);
    wait(&status);
    data->last_exit_code = status >> 8;
}

void ms_execute_commands(data_t *data)
{
    int fds[2];
    int in_fd = 0;
    pid_t pid;
    token_t *current;
    token_t *next_command;

    current = data->tokens;
    while (current != NULL)
    {
        char **args;
        next_command = current;
        while (next_command != NULL && next_command->type != T_PIPE)
            next_command = next_command->next;
        args = ms_get_full_args(current, next_command);
        if (next_command != NULL)
            pipe(fds);
        pid = fork();
        if (pid == 0)
            execute_child_process(args, fds, in_fd, next_command, data);
        else if (pid < 0)
        {
            perror("fork");
            exit(EXIT_FAILURE);
        }
        else
            handle_parent_process(fds, &in_fd, next_command, args, data);
        if (next_command != NULL)
            current = next_command->next;
        else
            current = NULL;
    }
}
