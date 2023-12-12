/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   executor.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: trstn4 <trstn4@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/08/21 19:24:57 by trstn4        #+#    #+#                 */
/*   Updated: 2023/12/12 23:32:11 by trstn4        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void ms_throw_error(data_t *data, token_t *current)
{
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
}

void handle_parent_process(int *in_fd, int is_pipe, int fds[2], pid_t pid, data_t *data) {
    int status;

    if (*in_fd != 0) {
        close(*in_fd);
    }
    if (is_pipe) {
        close(fds[1]);
        *in_fd = fds[0];
    } else {
        *in_fd = 0;
    }

    print_new_prompt = 1;
    waitpid(pid, &status, 0); // Wait for the child process to finish
    data->last_exit_code = WEXITSTATUS(status);
    print_new_prompt = 0;
}

void execute_child_process(data_t *data, token_t *current, char **args, int in_fd, int is_pipe, int is_redirect, int fds[2]) {
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
        if (ms_setup_redirection(current) == -1) {
            exit(EXIT_FAILURE);
        }
    }

    // Execute command
    if (ms_is_builtin_command(args[0])) {
        ms_run_builtin(data, args, current);
        exit(EXIT_SUCCESS);
    } else {
        ms_throw_error(data, current);
        execve(args[0], args, data->envp);
        if (errno == ENOENT)
        {
            perror("execve");
            exit(127);
        }
        else if (errno == EACCES)
        {
            perror("execve");
            exit(126);
        }
        else
        {
            perror("execve");
            exit(EXIT_FAILURE);
        }
    }
}

void ms_execute_commands(data_t *data) {
    pid_t pid;
    token_t *current;
    token_t *next_command;
    char **args;
    int fds[2];
    int in_fd = 0;

    current = data->tokens;
    token_t *first_command_token = data->tokens;
    while (current != NULL) {
        token_t *temp = current;
        int br2 = 0;
        ms_handle_heredoc(data, temp, first_command_token, &br2);
        if (br2 == 1)
            break;
            
        next_command = current;

        int is_pipe = 0;
        int is_redirect = 0;
        
        int br = 0;
        next_command = ms_check_redirects(data, next_command, &is_pipe, &is_redirect, &br);
        if (br == 1)
            break;

        args = ms_get_full_args(current, next_command); 
        
        // Handle built-in commands differently when they are part of a pipeline
        if (ms_is_builtin_command(args[0]) && !is_pipe && !is_redirect) {
            ms_run_builtin(data, args, current);
        } else {
            // Set up pipe if needed
            if (is_pipe) {
                pipe(fds);
            }

            pid = fork();
            if (pid == 0) { // Child process
                execute_child_process(data, current, args, in_fd, is_pipe, is_redirect, fds);
            } else if (pid < 0) {
                perror("fork");
                exit(EXIT_FAILURE);
            }
            handle_parent_process(&in_fd, is_pipe, fds, pid, data);
        }

        ms_free_2d_array(args);
        current = next_command ? next_command->next : NULL;
    }
}
