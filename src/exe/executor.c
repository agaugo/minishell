/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   executor.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: trstn4 <trstn4@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/08/21 19:24:57 by trstn4        #+#    #+#                 */
/*   Updated: 2023/12/15 15:37:49 by trstn4        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ms_identify_and_exec(t_data *data, t_token_t *current, char **args)
{
	if (ms_is_builtin_command(args[0]))
	{
		ms_run_builtin(data, args, current);
		exit(EXIT_SUCCESS);
	}
	else
	{
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

void	handle_parent_process(t_exec_t_data *cmd_data, int fds[2])
{
	if (cmd_data->in_fd != 0)
		close(cmd_data->in_fd);
	if (cmd_data->is_pipe)
	{
		close(fds[1]);
		cmd_data->in_fd = fds[0];
	}
	else
		cmd_data->in_fd = 0;
	g_print_new_prompt = 1;
	add_pid(cmd_data, cmd_data->pid);
}

void	execute_child_process(t_data *data, t_exec_t_data *cmd_data,
			t_token_t *current, int fds[2])
{
	if (cmd_data->in_fd != 0)
	{
		dup2(cmd_data->in_fd, STDIN_FILENO);
		close(cmd_data->in_fd);
	}
	if (cmd_data->is_pipe)
	{
		dup2(fds[1], STDOUT_FILENO);
		close(fds[0]);
		close(fds[1]);
	}
	if (cmd_data->is_redirect)
	{
		if (ms_setup_redirection(current) == -1)
			exit(EXIT_FAILURE);
	}
	ms_identify_and_exec(data, current, cmd_data->args);
}

void	ms_get_args_and_exec(t_data *data, t_exec_t_data *cmd_data)
{
	cmd_data->args = ms_get_full_args(cmd_data->current,
			cmd_data->next_command);
	if (ms_is_builtin_command(cmd_data->args[0]) && !cmd_data->is_pipe
		&& !cmd_data->is_redirect)
		ms_builtin_exitcode(data, cmd_data);
	else
	{
		if (cmd_data->is_pipe)
			pipe(cmd_data->fds);
		cmd_data->pid = fork();
		if (cmd_data->pid == 0)
			execute_child_process(data, cmd_data, cmd_data->current,
				cmd_data->fds);
		else if (cmd_data->pid < 0)
		{
			perror("fork");
			exit(EXIT_FAILURE);
		}
		handle_parent_process(cmd_data, cmd_data->fds);
	}
	ms_free_2d_array(cmd_data->args);
}

void	ms_execute_commands(t_data *data)
{
	t_exec_t_data	cmd_data;

	cmd_data.in_fd = 0;
	cmd_data.current = data->tokens;
	cmd_data.first_command_token = data->tokens;
	cmd_data.num_pids = 0;
	cmd_data.pid_list = NULL;
	while (cmd_data.current != NULL)
	{
		cmd_data.is_pipe = 0;
		cmd_data.is_redirect = 0;
		if (ms_exe_check_syntax(data) == 1)
			break ;
		ms_handle_heredoc(data, cmd_data.current, cmd_data.first_command_token);
		cmd_data.next_command = ms_check_redirects(&cmd_data, cmd_data.current);
		ms_get_args_and_exec(data, &cmd_data);
		if (cmd_data.next_command != NULL)
			cmd_data.current = cmd_data.next_command->next;
		else
			cmd_data.current = NULL;
	}
	ms_wait_and_receive(data, &cmd_data);
}
