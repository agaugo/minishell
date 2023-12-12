/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   export.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: trstn4 <trstn4@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/23 17:46:14 by trstn4        #+#    #+#                 */
/*   Updated: 2023/12/12 13:08:37 by trstn4        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	ms_is_valid_identifier(const char *key)
{
	int	i;

	i = 0;
	if (!key || (!ft_isalpha(key[0]) && key[0] != '_'))
		return (0);
	while (key[i] && key[i] != '=')
	{
		if (!ft_isalnum(key[i]) && key[i] != '_')
			return (0);
		i++;
	}
	if (key[i] != '=')
		return (1);
	return (1);
}

static int	ms_get_env_size(char **envp)
{
	int	size;

	size = 0;
	while (envp[size])
		size++;
	return (size);
}

static void	ms_add_to_env(data_t *data, char *key)
{
	char	**new_envp;
	int		size;

	size = ms_get_env_size(data->envp);
	new_envp = memory_realloc(data->envp, (size + 2) * sizeof(char *));
	if (!new_envp)
	{
		perror("Failed to reallocate memory for envp");
		exit(EXIT_FAILURE);
	}
	new_envp[size] = ft_strdup(key);
	new_envp[size + 1] = NULL;
	data->envp = new_envp;
}

void	ms_export_command(data_t *data, token_t *token)
{
	token_t	*current_token;
	char	*key;
	char	*value;
	char	*new_assignment;
	int		i;
	int		equals_index;

	data->last_exit_code = 0;
	current_token = token->next;
	if (!current_token)
	{
		i = 0;
		while (data->envp[i])
		{
			printf("%s\n", data->envp[i]);
			i++;
		}
		return;
	}
	while (current_token != NULL)
	{
		key = current_token->value;
		if (current_token->type == T_PIPE)
			break;
		if (!ms_is_valid_identifier(key))
		{
			fprintf(stderr, "export: `%s': not a valid identifier\n", key);
			data->last_exit_code = 1;
			current_token = current_token->next;
			continue;
		}
		equals_index = -1;
		for (i = 0; key[i]; i++)
		{
			if (key[i] == '=')
			{
				equals_index = i;
				break;
			}
		}
		if (equals_index != -1)
		{
			key[equals_index] = '\0';
			value = key + equals_index + 1;

			if (strchr(value, ' ') || strchr(value, '\t') || strchr(value, '\"') || strchr(value, '\''))
			{
				new_assignment = (char *)allocate_memory(strlen(key) + strlen(value) + 4);
				sprintf(new_assignment, "%s=\"%s\"", key, value); 
			}
			else
			{
				new_assignment = allocate_memory(strlen(key) + strlen(value) + 2);
				sprintf(new_assignment, "%s=%s", key, value); 
			}
			for (i = 0; data->envp[i]; i++)
			{
				if (ft_strncmp(data->envp[i], key, strlen(key)) == 0 && data->envp[i][strlen(key)] == '=')
				{
					free_memory(data->envp[i]);
					data->envp[i] = ft_strdup(new_assignment);
					break;
				}
			}
			if (data->envp[i] == NULL)
				ms_add_to_env(data, new_assignment);
			free_memory(new_assignment);
			current_token = current_token->next;
			continue;
		}
		current_token = current_token->next;
	}
}
