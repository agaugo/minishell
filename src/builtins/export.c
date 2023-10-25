/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   export.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: trstn4 <trstn4@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/23 17:46:14 by trstn4        #+#    #+#                 */
/*   Updated: 2023/10/24 21:52:04 by trstn4        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	find_env_index(char **envp, const char *key)
{
	int	i;
	int	key_len;

	i = 0;
	key_len = strlen(key);
	while (envp[i])
	{
		if (strncmp(envp[i], key, key_len) == 0 && envp[i][key_len] == '=')
		{
			return (i);
		}
		i++;
	}
	return (-1);
}

void	ms_export_command(token_t *_token, char ***envp)
{
	int		index;
			int size;
	char	**new_envp;

	// No arguments, just print the environment variables
	if (!_token->next)
	{
		for (int i = 0; (*envp)[i]; i++)
		{
			printf("%s\n", (*envp)[i]);
		}
	}
	else
	{
		char *key = _token->next->value;
			// Assuming value is the argument given to export
		index = find_env_index(*envp, key);
		// If key is already in the environment, update it
		if (index != -1)
		{
			free((*envp)[index]);
			(*envp)[index] = strdup(key);
		}
		else
		{
			// Add the new key-value pair to the environment
			for (size = 0; (*envp)[size]; size++)
				;
			new_envp = realloc(*envp, (size + 2) * sizeof(char *));
			if (!new_envp)
			{
				perror("Failed to reallocate memory for envp");
				exit(EXIT_FAILURE);
			}
			new_envp[size] = strdup(key);
			new_envp[size + 1] = NULL;
			*envp = new_envp;
		}
	}
}
