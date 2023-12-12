/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   env.c                                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: trstn4 <trstn4@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/24 23:38:22 by trstn4        #+#    #+#                 */
/*   Updated: 2023/12/12 15:49:22 by trstn4        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	print_env(data_t *data)
{
	int	i;

	i = 0;
	while (data->envp[i])
	{
		printf("%s\n", data->envp[i]);
		i++;
	}
}

void	update_env(data_t *data, char *key, char *new_assignment)
{
	int	i;

	i = 0;
	while (data->envp[i])
	{
		if (ft_strncmp(data->envp[i], key, strlen(key)) == 0
			&& data->envp[i][strlen(key)] == '=')
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

void	ms_add_to_env(data_t *data, char *key)
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

char *ft_getenv(char **envp, char *key)
{
    int i;
    int len;

    i = 0;
    len = ft_strlen(key);
    while (envp[i] != NULL)
    {
        if (ft_strncmp(envp[i], key, len) == 0)
            return (ft_strdup(envp[i] + (len + 1)));
        i++;
    }
    return (NULL);
}

char	**ms_clone_envp(char **envp)
{
	int		count;
	char	**new_envp;
	int		i;

	i = 0;
	count = 0;
	while (envp[count])
		count++;
	new_envp = (char **)allocate_memory(sizeof(char *) * (count + 1));
	while (i < count)
	{
		new_envp[i] = ft_strdup(envp[i]);
		if (!new_envp[i])
		{
			ms_handle_error(EXIT_FAILURE,
				"Failed to duplicate string for new_envp");
		}
		i++;
	}
	new_envp[count] = NULL;
	// debug("envp alloc\n"); //for testing
	return (new_envp);
}
