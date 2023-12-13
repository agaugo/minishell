/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   unset.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: trstn4 <trstn4@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/24 19:40:15 by trstn4        #+#    #+#                 */
/*   Updated: 2023/12/13 15:06:22 by trstn4        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	shift_envp_array(t_data *data, int start_index)
{
	int	i;

	i = start_index;
	while (data->envp[i])
	{
		data->envp[i] = data->envp[i + 1];
		i++;
	}
}

void	resize_envp_array(t_data *data)
{
	int		size;
	char	**new_envp;

	size = ms_get_env_size(data->envp);
	new_envp = memory_realloc(data->envp, size * sizeof(char *));
	if (!new_envp)
	{
		perror("Failed to reallocate memory for envp");
		exit(EXIT_FAILURE);
	}
	data->envp = new_envp;
	data->envp[size - 1] = NULL;
}

void	remove_env_var(t_data *data, char *key)
{
	int	index;

	index = ms_find_env_index(data->envp, key);
	if (index != -1)
	{
		free_memory(data->envp[index]);
		shift_envp_array(data, index);
		resize_envp_array(data);
	}
}

void	ms_unset_command(t_data *data, t_token_t *token)
{
	if (!token->next)
		return ;
	token = token->next;
	while (token)
	{
		if (token->type == T_PIPE)
			break ;
		remove_env_var(data, token->value);
		token = token->next;
	}
}
