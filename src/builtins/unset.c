/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   unset.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: trstn4 <trstn4@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/24 19:40:15 by trstn4        #+#    #+#                 */
/*   Updated: 2023/12/09 21:41:29 by trstn4        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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
	if (!token->next)
		return ;
	
    token = token->next; // Move to the first argument (skip the "unset" token)
    while (token)
    {
		if (token->type == T_PIPE)
			break;

        char *key = token->value;
        int index = ms_find_env_index(data->envp, key);
        if (index != -1)
        {
            // Free the environment variable at the specified index
            free(data->envp[index]);
            // Shift the remaining environment variables
            for (int i = index; i < ms_get_env_size(data->envp) - 1; i++)
            {
                data->envp[i] = data->envp[i + 1];
            }
            // Reduce the size of the environment pointer array
            int size = ms_get_env_size(data->envp);
            char **new_envp = realloc(data->envp, size * sizeof(char *));
            if (!new_envp)
            {
                perror("Failed to reallocate memory for envp");
                exit(EXIT_FAILURE);
            }
            data->envp = new_envp;
            data->envp[size - 1] = NULL; // Set the last pointer to NULL
        }
        token = token->next;
    }
}
