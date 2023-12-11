/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   export.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: trstn4 <trstn4@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/23 17:46:14 by trstn4        #+#    #+#                 */
/*   Updated: 2023/12/09 16:53:35 by trstn4        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int ms_is_valid_identifier(const char *key)
{
    int i = 0;

    // Check the key part before the '='
    if (!key || (!ft_isalpha(key[0]) && key[0] != '_'))
        return (0);

    while (key[i] && key[i] != '=')
    {
        if (!ft_isalnum(key[i]) && key[i] != '_')
            return (0);
        i++;
    }

    // If there's no '=', then it's a standalone identifier which is valid
    if (key[i] != '=')
        return (1);

    // If there is an '=', it's a key=value pair, and the key part is valid
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
	new_envp = realloc(data->envp, (size + 2) * sizeof(char *));
	if (!new_envp)
	{
		perror("Failed to reallocate memory for envp");
		exit(EXIT_FAILURE);
	}
	new_envp[size] = ft_strdup(key);
	new_envp[size + 1] = NULL;
	data->envp = new_envp;
}

void ms_export_command(data_t *data, token_t *token)
{
    token_t *current_token = token->next;
    char *key;
    char *value;
    char *new_assignment;
    int i, equals_index;

    data->last_exit_code = 0; // Default to success

    if (!current_token) // No arguments to export command
    {
        for (i = 0; data->envp[i]; i++)
            printf("%s\n", data->envp[i]);
        return;
    }

    while (current_token != NULL)
    {
        key = current_token->value;

		if (current_token->type == T_PIPE)
			break;

        // Validate the key first
        if (!ms_is_valid_identifier(key))
        {
            fprintf(stderr, "export: `%s': not a valid identifier\n", key);
            data->last_exit_code = 1;
            current_token = current_token->next;
            continue;
        }

        equals_index = -1;
        for (i = 0; key[i]; i++) // Find '=' character
        {
            if (key[i] == '=')
            {
                equals_index = i;
                break;
            }
        }

        if (equals_index != -1) // '=' found
        {
            key[equals_index] = '\0'; // Split key and value
            value = key + equals_index + 1;

            // Check if the value needs quoting
            if (strchr(value, ' ') || strchr(value, '\t') || strchr(value, '\"') || strchr(value, '\''))
            {
                // Create new key-value assignment string with quotes
                new_assignment = (char *)allocate_memory(strlen(key) + strlen(value) + 4); // Space for key, '=', quotes, and null terminator
                sprintf(new_assignment, "%s=\"%s\"", key, value); 
            }
            else
            {
                // Create new key-value assignment string without quotes
                new_assignment = allocate_memory(strlen(key) + strlen(value) + 2); // Space for key, '=', and null terminator
                sprintf(new_assignment, "%s=%s", key, value); 
            }

            // Check if the variable already exists, and if so, update its value
            for (i = 0; data->envp[i]; i++)
            {
                if (ft_strncmp(data->envp[i], key, strlen(key)) == 0 && data->envp[i][strlen(key)] == '=')
                {
                    // Update the existing environment variable with the new value
                    free_memory(data->envp[i]);
                    data->envp[i] = ft_strdup(new_assignment);
                    break;
                }
            }

            // If the variable didn't exist, add the new assignment to the environment
            if (data->envp[i] == NULL)
                ms_add_to_env(data, new_assignment);
            
            free_memory(new_assignment);
            current_token = current_token->next;
            continue;
        }

        // Handle the case where there's no '=' sign
        // You can choose to implement this part according to your requirements.
        // For example, you can set the variable to an empty string or ignore it.

        current_token = current_token->next;
    }
}
