/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   unset.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: trstn4 <trstn4@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/24 19:40:15 by trstn4        #+#    #+#                 */
/*   Updated: 2023/10/24 19:46:12 by trstn4        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	find_env_index(char **envp, const char *key)
{
	int	i;
	int	key_len;

	i = 0;
	key_len = strlen(key);
	while (envp[i])
	{
		if (ft_strncmp(envp[i], key, key_len) == 0 && envp[i][key_len] == '=')
		{
			return (i);
		}
		i++;
	}
	return (-1);
}

void	ms_unset_command(token_t *_token, char ***envp)
{
	char	*key;
	int		index;
	int		size;
	char	**new_envp;

	if (!_token->next)
	{
		printf("unset: missing argument\n");
		return ;
	}
	key = _token->next->value;
	index = find_env_index(*envp, key);
	if (index == -1)
	{
		printf("unset: %s: not found\n", key);
		return ;
	}
	free((*envp)[index]);
	// Shift the remaining environment variables to fill the gap
	for (int i = index; (*envp)[i]; i++)
	{
		(*envp)[i] = (*envp)[i + 1];
	}
	// Resize the environment array
	for (size = 0; (*envp)[size]; size++)
		;
	new_envp = realloc(*envp, size * sizeof(char *));
	if (!new_envp)
	{
		perror("Failed to reallocate memory for envp");
		exit(EXIT_FAILURE);
	}
	*envp = new_envp;
}
