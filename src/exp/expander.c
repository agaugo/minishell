/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   expander.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: trstn4 <trstn4@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/08/21 19:24:57 by trstn4        #+#    #+#                 */
/*   Updated: 2023/11/01 16:24:55 by trstn4        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*
expand_dollarsign:
- Environment Variables: Recognize patterns like $VAR_NAME or ${VAR_NAME} and replace them with the value of the environment variable.
- Special Variables: Shells often have special variables (e.g., $? to get the exit status of the last command).
- Arithmetic Evaluation: Some shells allow arithmetic expressions, e.g., $((2 + 2)) should expand to 4.

expand_quotes:
- Double Quotes ("): Preserve the literal value of all characters within the quotes, but still allow the expansion of variables. Example: echo "$HOME is your home directory" should expand $HOME but not interpret other characters specially.
- Single Quotes ('): Preserve the literal value of all characters within the quotes. No expansions should occur inside single quotes. Example: echo '$HOME is your home directory' should not expand $HOME.
- Backticks (`): Command substitution. The enclosed command is executed, and the output replaces the backticks expression. Example: `date` should be replaced with the current date.

Tilde Expansion (~):
- Recognize the ~ at the start of a word as a shorthand for the user's home directory.

Brace Expansion:
- Expand expressions like {a,b,c} to a b c. Example: echo {a,b,c}d should produce the output ad bd cd.

Escape Characters: Recognize the backslash \ to escape the next character, making it literal. For instance, \$ should be interpreted as a literal dollar sign, not the start of a variable expansion.
*/

void	print_list(token_t *head)
{
	token_t	*current_token;
	int		i;

	current_token = head;
	i = 0;
	printf("----------- expander debug -----------------------------------\n");
	while (current_token)
	{
		printf("Token %d: %s, Type: %d\n", i, current_token->value,
			current_token->type);
		current_token = current_token->next;
		i++;
	}
	printf("--------------------------------------------------------------\n");
}

// char *expand_quotes(data_t data)
// {
//     // TODO: Add the logic to handle the double, single quotes and backticks.
//     return NULL; // Placeholder return
// }

char *expand_tilde(data_t data, char *token_value)
{
    int index = find_env_index(data.envp, "HOME");
    if (index == -1) {
        perror("Environment Variable Not Found");
        return token_value;
    }
    char *var_val = strchr(data.envp[index], '=') + 1;
    return strdup(var_val);
}

char *expand_dollarsign(data_t data, char *token_value)
{
    int index = find_env_index(data.envp, token_value);
    if (index == -1) {
        perror("Environment Variable Not Found");
        return token_value;
    }
    char *var_val = strchr(data.envp[index], '=') + 1;
    return strdup(var_val);
}

char *expand_quotes(data_t data, char *token_value)
{
    char    *result;
    char    *var_name;
    char    *var_value;
    int     i = 0, j = 0, k, var_len;

    result = malloc(strlen(token_value) * 2 + 1);
    if (!result)
        return NULL;

    while (token_value[i])
    {
        if (token_value[i] == '$')
        {
            i++;
            k = 0;
            var_name = malloc(strlen(token_value) + 1);
            while (isalnum(token_value[i + k]) || token_value[i + k] == '_')
            {
                var_name[k] = token_value[i + k];
                k++;
            }
            var_name[k] = '\0';

            var_value = expand_dollarsign(data, var_name);

            if (var_value != var_name)
            {
                var_len = strlen(var_value);
                strcpy(result + j, var_value);
                j += var_len;
            }
            else
            {
                strcpy(result + j, "$");
                strcpy(result + j + 1, var_name);
                j += k + 1;
            }

            free(var_name);
            i += k;
        }
        else
        {
            result[j] = token_value[i];
            i++;
            j++;
        }
    }
    result[j] = '\0';
    return result;
}

void	ms_expander(data_t data)
{
	token_t	*current_token;
    token_t *temp;
    
	current_token = data.tokens;
    temp = NULL;
	while (current_token)
	{
        if (current_token->type == T_TILDE)
        {
            current_token->value = expand_tilde(data, current_token->value);
            current_token->type = T_WORD;
        }
        else if (current_token->type == T_ENV_VARIABLE)
        {
            if (strcmp(data.tokens->next->value, "?") == 0)
                current_token->value = ft_itoa(data.last_exit_code);
            else
                current_token->value = expand_dollarsign(data, current_token->next->value);
            current_token->type = T_WORD;
            temp = current_token->next;
            current_token->next = current_token->next->next;
            free(temp);
            temp = NULL;
        }
        else if (current_token->type == T_DOUBLE_QUOTE)
        {
            current_token->value = expand_quotes(data, current_token->value);
            current_token->type = T_WORD;
        }
		current_token = current_token->next;
	}

    // print_list(data.tokens);
}
