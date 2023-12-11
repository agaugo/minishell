/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   env.c                                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: trstn4 <trstn4@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/24 23:38:22 by trstn4        #+#    #+#                 */
/*   Updated: 2023/12/09 17:19:58 by trstn4        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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
