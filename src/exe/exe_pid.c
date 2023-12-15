/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   exe_pid.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: trstn4 <trstn4@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/08/21 19:24:57 by trstn4        #+#    #+#                 */
/*   Updated: 2023/12/15 15:37:55 by trstn4        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	add_pid(t_exec_t_data *cmd_data, pid_t new_pid)
{
	t_pid_node	*new_node;
	t_pid_node	*current;

	new_node = malloc(sizeof(t_pid_node));
	if (new_node == NULL)
	{
		perror("Failed to allocate memory for PID node");
		exit(EXIT_FAILURE);
	}
	new_node->pid = new_pid;
	new_node->next = NULL;
	if (cmd_data->pid_list == NULL)
		cmd_data->pid_list = new_node;
	else
	{
		current = cmd_data->pid_list;
		while (current->next != NULL)
			current = current->next;
		current->next = new_node;
	}
}

void	free_pid_list(t_pid_node *head)
{
	t_pid_node	*current;
	t_pid_node	*next;

	current = head;
	while (current != NULL)
	{
		next = current->next;
		free(current);
		current = next;
	}
}

void	ms_wait_and_receive(t_data *data, t_exec_t_data *cmd_data)
{
	t_pid_node	*current_node;
	int			status;

	status = 0;
	current_node = cmd_data->pid_list;
	while (current_node != NULL)
	{
		waitpid(current_node->pid, &status, 0);
		if (current_node->next == NULL && WIFEXITED(status))
			data->last_exit_code = WEXITSTATUS(status);
		current_node = current_node->next;
	}
	if (cmd_data->last_is_builtin)
		data->last_exit_code = cmd_data->builtin_exit_status;
	free_pid_list(cmd_data->pid_list);
	g_print_new_prompt = 0;
}
