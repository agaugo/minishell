/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   unset.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: trstn4 <trstn4@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/24 19:40:15 by trstn4        #+#    #+#                 */
/*   Updated: 2023/11/28 16:38:39 by trstn4        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	ms_shift_env_vars(data_t *data, int index)
{
	int	i;

	i = index;
	while (data->envp[i])
	{
		data->envp[i] = data->envp[i + 1];
		i++;
	}
}

static int	ms_get_env_size(char **envp)
{
	int	size;

	size = 0;
	while (envp[size])
		size++;
	return (size);
}

void	ms_unset_command(data_t *data, token_t *token)
{
	char	*key;
	int		index;
	char	**new_envp;
	int		size;

	if (!token->next)
		return ;
	key = token->next->value;
	index = ms_find_env_index(data->envp, key);
	if (index == -1)
		return ;
	free(data->envp[index]);
	ms_shift_env_vars(data, index);
	size = ms_get_env_size(data->envp);
	new_envp = realloc(data->envp, size * sizeof(char *));
	if (!new_envp)
	{
		perror("Failed to reallocate memory for envp");
		exit(EXIT_FAILURE);
	}
	data->envp = new_envp;
}
