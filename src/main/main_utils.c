/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main_utils.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: trstn4 <trstn4@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/08/21 19:24:57 by trstn4        #+#    #+#                 */
/*   Updated: 2023/12/13 15:37:59 by trstn4        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ms_make_data_struct(t_data *data, char **envp)
{
	ft_memset(data, 0, sizeof(t_data));
	data->envp = ms_clone_envp(envp);
	data->last_exit_code = 0;
	data->heredoc_tmp_file = NULL;
	data->last_path = ms_get_current_working_dir();
}

t_token_t	*ms_rm_input(t_token_t *current)
{
	t_token_t	*temp;
	t_token_t	*next_temp;
	t_token_t	*last_file;

	last_file = current;
	if (last_file->next && last_file->next->type == T_WORD)
	{
		while (last_file->next && last_file->next->type == T_WORD)
			last_file = last_file->next;
		if (current->next != last_file)
		{
			temp = current->next;
			current->next = last_file;
			while (temp != last_file)
			{
				next_temp = temp->next;
				if (temp->value)
					free_memory(temp->value);
				free_memory(temp);
				temp = next_temp;
			}
		}
	}
	current = last_file->next;
	return (last_file->next);
}

t_token_t	*ms_rtn_curr(t_token_t *current)
{
	if (current->type == T_REDIRECT_IN)
		current = ms_rm_input(current);
	else
		current = current->next;
	return (current);
}

void	remove_intermediate_input_redirections(t_data *data)
{
	t_token_t	*current;
	int			skip;

	skip = 0;
	current = data->tokens;
	if (data == NULL || data->tokens == NULL)
		return ;
	while (current != NULL)
	{
		if (current->type == T_PIPE)
			skip = 0;
		if (skip == 1)
		{
			current = current->next;
			continue ;
		}
		if (ms_is_builtin_command(current->value) == 1)
		{
			current = current->next;
			skip = 1;
			continue ;
		}
		current = ms_rtn_curr(current);
	}
}
