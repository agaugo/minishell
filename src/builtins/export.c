/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   export.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: trstn4 <trstn4@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/23 17:46:14 by trstn4        #+#    #+#                 */
/*   Updated: 2023/10/25 13:52:30 by trstn4        ########   odam.nl         */
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

void ms_export_command(data_t data) {
    // No arguments, just print the environment variables
    if (!data.tokens->next) {
        for (int i = 0; data.envp[i]; i++) {
            printf("%s\n", data.envp[i]);
        }
    } else {
        char *key = data.tokens->next->value;  // Assuming value is the argument given to export
        int index = find_env_index(data.envp, key);

        // If key is already in the environment, update it
        if (index != -1) {
            free(data.envp[index]);
            data.envp[index] = strdup(key);
        } else {
            // Add the new key-value pair to the environment
            int size;
            for (size = 0; (data.envp)[size]; size++);

            char **new_envp = realloc(data.envp, (size + 2) * sizeof(char *));
            if (!new_envp) {
                perror("Failed to reallocate memory for envp");
                exit(EXIT_FAILURE);
            }

            new_envp[size] = strdup(key);
            new_envp[size + 1] = NULL;
            data.envp = new_envp;
        }
    }
}
