/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   export.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: trstn4 <trstn4@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/23 17:46:14 by trstn4        #+#    #+#                 */
/*   Updated: 2023/11/02 12:44:43 by trstn4        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	is_valid_identifier(const char *key)
{
    if (!key || (!isalpha(key[0]) && key[0] != '_')) {
        return (0);
    }
    int has_equal_sign = 0;
    int in_quotes = 0;
    for (int i = 1; key[i]; i++) {
        if (key[i] == '\"' || key[i] == '\'') {
            in_quotes = !in_quotes;  // Toggle quote flag when encountering a quote
            continue;
        }
        if (!in_quotes && !isalnum(key[i]) && key[i] != '_' && key[i] != '=') {
            return (0);
        }
        if (key[i] == '=') {
            if (has_equal_sign) {
                return (0);
            }
            has_equal_sign = 1;
        }
    }
    return (1);
}

int	find_env_index(char **envp, const char *key)
{
	int	i;
	int	key_len;

	i = 0;
	key_len = ft_strlen(key);
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

void ms_export_command(data_t *data) {
    // No arguments, just print the environment variables
    if (!data->tokens->next) {
        for (int i = 0; data->envp[i]; i++) {
            printf("%s\n", data->envp[i]);
        }
    } else {
    char *key = data->tokens->next->value;

        if (!is_valid_identifier(key)) {
            fprintf(stderr, "export: `%s': not a valid identifier\n", key);
            // Set exit status to 1 indicating an error occurred
            // You might have to modify this line according to your data structure
            data->last_exit_code = 1;
            return;
        }
        else {
            // Add the new key-value pair to the environment
            int size;
            for (size = 0; (data->envp)[size]; size++);

            char **new_envp = realloc(data->envp, (size + 2) * sizeof(char *));
            if (!new_envp) {
                perror("Failed to reallocate memory for envp");
                exit(EXIT_FAILURE);
            }

            new_envp[size] = ft_strdup(key);
            new_envp[size + 1] = NULL;
            data->envp = new_envp;
        }
    }
}
