/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   memory.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: trstn4 <trstn4@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/08/21 19:24:57 by trstn4        #+#    #+#                 */
/*   Updated: 2023/12/14 00:19:17 by trstn4        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	free_token_list(t_token_t *head)
{
	t_token_t	*current;
	t_token_t	*next;

	current = head;
	while (current != NULL)
	{
		next = current->next;
		free_memory(current->value);
		free_memory(current);
		current = next;
	}
}

void	wipe_fd_and_heredoc(t_data *data)
{
	if (data->std_out)
		close(data->std_out);
	if (data->std_in)
		close(data->std_in);
	ft_memset(data, 0, sizeof(t_data));
	if (access("/tmp/minishell_heredoc", F_OK) == 0)
	{
		if (unlink("/tmp/minishell_heredoc") == -1)
		{
			perror("unlink");
			return ;
		}
	}
}

void	wipe_data_struct(t_data *data)
{
	char	**env;

	if (data == NULL)
		return ;
	free_memory(data->user_input);
	free_memory(data->heredoc_tmp_file);
	free_memory(data->last_path);
	free_token_list(data->tokens);
	if (data->envp != NULL)
	{
		env = data->envp;
		while (*env != NULL)
		{
			free_memory(*env);
			env++;
		}
		free_memory(data->envp);
	}
	wipe_fd_and_heredoc(data);
}
