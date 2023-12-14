/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   env.c                                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: trstn4 <trstn4@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/24 23:38:22 by trstn4        #+#    #+#                 */
/*   Updated: 2023/12/14 00:23:53 by trstn4        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	print_env(t_data *data)
{
	int	i;

	i = 0;
	while (data->envp[i])
	{
		printf("%s\n", data->envp[i]);
		i++;
	}
}

void	update_env(t_data *data, char *key, char *new_assignment)
{
	int	i;

	i = 0;
	while (data->envp[i])
	{
		if (ft_strncmp(data->envp[i], key, ft_strlen(key)) == 0
			&& data->envp[i][ft_strlen(key)] == '=')
		{
			free_memory(data->envp[i]);
			data->envp[i] = ft_strdup(new_assignment);
			break ;
		}
		i++;
	}
	if (data->envp[i] == NULL)
		ms_add_to_env(data, new_assignment);
}

int	ms_get_env_size(char **envp)
{
	int	size;

	size = 0;
	while (envp[size])
		size++;
	return (size);
}

void	ms_add_to_env(t_data *data, char *key)
{
	char	**new_envp;
	int		size;

	size = ms_get_env_size(data->envp);
	new_envp = memory_realloc(data->envp, (size + 2) * sizeof(char *));
	if (!new_envp)
	{
		ms_handle_error(EXIT_FAILURE, "Failed to reallocate memory for envp");
		exit(EXIT_FAILURE);
	}
	new_envp[size] = ft_strdup(key);
	new_envp[size + 1] = NULL;
	data->envp = new_envp;
}

int	ms_find_env_index(char **envp, const char *key)
{
	int	i;
	int	key_len;

	i = 0;
	key_len = ft_strlen(key);
	while (envp[i])
	{
		if (ft_strncmp(envp[i], key, key_len) == 0 && envp[i][key_len] == '=')
			return (i);
		i++;
	}
	return (-1);
}
