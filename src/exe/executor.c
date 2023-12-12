/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   executor.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: trstn4 <trstn4@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/08/21 19:24:57 by trstn4        #+#    #+#                 */
/*   Updated: 2023/12/13 00:23:59 by trstn4        ########   odam.nl         */
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

	if (*in_fd != 0)
		close(*in_fd);
	if (is_pipe)
	{
		close(fds[1]);
		*in_fd = fds[0];
	}
	else
		*in_fd = 0;
	print_new_prompt = 1;
	waitpid(pid, &status, 0);
	data->last_exit_code = WEXITSTATUS(status);
	print_new_prompt = 0;
}

void    ms_identify_and_exec(data_t *data, token_t *current, char **args)
{
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

	if (is_redirect) {
		if (ms_setup_redirection(current) == -1) {
			exit(EXIT_FAILURE);
		}
	}
	ms_identify_and_exec(data, current, args);
}

void ms_get_args_and_exec(data_t *data, exec_data_t *cmd_data)
{
	cmd_data->args = ms_get_full_args(cmd_data->current, cmd_data->next_command);
	if (ms_is_builtin_command(cmd_data->args[0]) && !cmd_data->is_pipe && !cmd_data->is_redirect) {
		ms_run_builtin(data, cmd_data->args, cmd_data->current);
	} else {
		if (cmd_data->is_pipe)
			pipe(cmd_data->fds);
		cmd_data->pid = fork();
		if (cmd_data->pid == 0)
			execute_child_process(data, cmd_data->current, cmd_data->args, cmd_data->in_fd, cmd_data->is_pipe, cmd_data->is_redirect, cmd_data->fds);
		else if (cmd_data->pid < 0) {
			perror("fork");
			exit(EXIT_FAILURE);
		}
		handle_parent_process(&cmd_data->in_fd, cmd_data->is_pipe, cmd_data->fds, cmd_data->pid, data);
	}
	ms_free_2d_array(cmd_data->args);
}

void ms_execute_commands(data_t *data) {
	exec_data_t cmd_data;
	cmd_data.in_fd = 0;
	cmd_data.current = data->tokens;
	cmd_data.first_command_token = data->tokens;

	while (cmd_data.current != NULL) {
		cmd_data.br2 = 0;
		cmd_data.is_pipe = 0;
		cmd_data.is_redirect = 0;
		cmd_data.br = 0;
		ms_handle_heredoc(data, cmd_data.current, cmd_data.first_command_token, &cmd_data.br2);
		if (cmd_data.br2 == 1)
			break;
		cmd_data.next_command = ms_check_redirects(data, cmd_data.current, &cmd_data.is_pipe, &cmd_data.is_redirect, &cmd_data.br);
		if (cmd_data.br == 1)
			break;
		ms_get_args_and_exec(data, &cmd_data);
		cmd_data.current = cmd_data.next_command ? cmd_data.next_command->next : NULL;
	}
}
