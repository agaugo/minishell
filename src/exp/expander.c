/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   expander.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: trstn4 <trstn4@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/08/21 19:24:57 by trstn4        #+#    #+#                 */
/*   Updated: 2023/12/09 21:46:40 by trstn4        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

#include <stdlib.h>
#include <string.h>

#include <stdlib.h>
#include <string.h>

#include <stdlib.h>
#include <string.h>

typedef struct s_quote_vars
{
	size_t	*i;
	size_t	*j;
	int		*in_single_quote;
	int		*in_double_quote;
	char	*cleaned_str;
}				t_quote_vars;

static void	ms_check_quotes2(const char *str, t_quote_vars *vars)
{
	if ((str[*vars->i] == '\'' || str[*vars->i] == '\"')
		&& !(*vars->in_single_quote) && !(*vars->in_double_quote)
		&& (*vars->i == 0 || *vars->i == strlen(str) - 1
			|| str[*vars->i - 1] == ' ' || str[*vars->i + 1] == ' '
			|| str[*vars->i + 1] == '\0'))
		(*vars->i)++;
	else if (str[*vars->i] == '\'' && str[*vars->i - 1] != ' '
		&& str[*vars->i + 1] != ' ' && !(*vars->in_single_quote)
		&& !(*vars->in_double_quote))
		(*vars->i)++;
	else if (str[*vars->i] == '\"' && str[*vars->i - 1] != ' '
		&& str[*vars->i + 1] == '\"' && !(*vars->in_single_quote)
		&& !(*vars->in_double_quote))
		(*vars->i) += 2;
	else
		vars->cleaned_str[(*vars->j)++] = str[(*vars->i)++];
}

static void	ms_check_quotes(const char *str, t_quote_vars *vars)
{
	if (str[*vars->i] == '\'' && !(*vars->in_double_quote)
		&& (*vars->i == 0 || str[*vars->i - 1] != '\\' || (*vars->i > 1
				&& str[*vars->i - 2] == '\\')))
	{
		*vars->in_single_quote = !(*vars->in_single_quote);
		(*vars->i)++;
	}
	else if (str[*vars->i] == '\"' && !(*vars->in_single_quote)
		&& (*vars->i == 0 || str[*vars->i - 1] != '\\' || (*vars->i > 1
				&& str[*vars->i - 2] == '\\')))
	{
		*vars->in_double_quote = !(*vars->in_double_quote);
		(*vars->i)++;
	}
	else
		ms_check_quotes2(str, vars);
}

static char	*ms_clean_quotes(t_quote_vars *vars, const char *str)
{
	char			*cleaned_str;
	size_t			i;
	size_t			j;
	int				sq;
	int				dq;

	i = 0;
	j = 0;
	sq = 0;
	dq = 0;
	cleaned_str = malloc(strlen(str) + 1);
	vars = &(t_quote_vars){&i, &j, &sq, &dq, cleaned_str};
	while (str[i])
		ms_check_quotes(str, vars);
	cleaned_str[j] = '\0';
	return (cleaned_str);
}

void handle_quotes(const char *input) {
    int in_single_quote = 0, in_double_quote = 0;
    char current_char;

    for (size_t i = 0; i < ft_strlen(input); i++) {
        current_char = input[i];

        // Handle single quote
        if (current_char == '\'' && !in_double_quote) {
            in_single_quote = !in_single_quote;
            printf("%c", current_char);  // Print the single quote
            continue;
        }

        // Handle double quote
        if (current_char == '\"' && !in_single_quote) {
            in_double_quote = !in_double_quote;
            printf("%c", current_char);  // Print the double quote
            continue;
        }

        // Print all characters
        printf("%c", current_char);
    }
}

void    print_list(token_t *head)
{
    token_t    *current_token;
    int        i;

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

char *expand_tilde(data_t *data, char *token_value)
{
    // Check if token starts with tilde and is followed by a slash or end of string
    if (token_value[0] == '~' && (token_value[1] == '/' || token_value[1] == '\0')) {
        int home_index = ms_find_env_index(data->envp, "HOME");
        if (home_index == -1) {
            perror("Environment Variable HOME Not Found");
            return strdup(token_value); // Return the original token if HOME not found
        }

        char *home_path = strchr(data->envp[home_index], '=') + 1;
        size_t new_size = strlen(home_path) + strlen(token_value);
        char *new_token_value = (char *)malloc(new_size);
        if (new_token_value == NULL) {
            perror("Memory Allocation Failed");
            return strdup(token_value); // Return the original token if allocation fails
        }

        strcpy(new_token_value, home_path); // Copy home directory
        strcat(new_token_value, token_value + 1); // Append the rest of the original token after tilde

        free(token_value); // Free the original token value
        return new_token_value; // Return the new token value
    }
    return strdup(token_value); // Return the original token if it doesn't start with tilde
}

char *expand_dollarsign(data_t *data, char *token_value)
{
    int index = ms_find_env_index(data->envp, token_value);
    if (index == -1) {
        return strdup("");  // Return empty string if not found
    }
    char *var_val = strchr(data->envp[index], '=') + 1;
    return strdup(var_val);
}

void remove_token(token_t **head, token_t *prev_token, token_t *current_token)
{
    if (!current_token) return; // Safety check

    if (prev_token == NULL) {
        // If removing the first token, update the head of the list
        *head = current_token->next;
    } else {
        // Link the previous token to the next of the current one
        prev_token->next = current_token->next;
    }

    // Free the current token
    free(current_token->value);
    free(current_token);
}

char *expand_quotes(data_t *data, char *token_value)
{
    char *result;
    char *var_name;
    char *var_value;
    int i = 0, j = 0, k, var_len;
    // int result_size = strlen(token_value) * 2 + 1;  // Initial allocation

    result = allocate_memory(4096);
    if (!result)
        return NULL;
    
    while (token_value[i])
    {
        if (token_value[i] == '$' && token_value[i+1] == '?')
        {
            char *exit_code_str = ft_itoa(data->last_exit_code);
            size_t exit_code_len = strlen(exit_code_str);

            // Check if exit code fits within the string, otherwise reallocate
            char *new_token_value = allocate_memory(strlen(token_value) + exit_code_len + 1);
            if (!new_token_value) {
                // Handle memory allocation error
            }

            // Copy characters before $?
            strncpy(new_token_value, token_value, i);

            // Copy exit code string
            strcpy(new_token_value + i, exit_code_str);

            // Copy characters after $? 
            strcpy(new_token_value + i + exit_code_len, token_value + i + 2);

            free(exit_code_str);
            free(token_value);
            token_value = new_token_value;
        }
        if (token_value[i] == '$' && token_value[i + 1] != '\'')
        {
            i++;
            k = 0;
            var_name = (char *)allocate_memory(strlen(token_value) + 1);
            memset(var_name, 0, ft_strlen(token_value) + 1);

            while (isalnum(token_value[i + k]) || token_value[i + k] == '_' || token_value[i + k] == '?')
            {
                var_name[k] = token_value[i + k];
                k++;
            }
            var_name[k] = '\0';

            if (k == 0)  // No variable name after '$'
            {
                result[j++] = '$';
            }
            else if (ft_strcmp(var_name, "?") == 0)
            {
                var_value = ft_itoa(data->last_exit_code);
                var_len = ft_strlen(var_value);
                strncpy(result + j, var_value, var_len);
                j += var_len;
                free(var_value);
            }
            else
            {
                var_value = expand_dollarsign(data, var_name);
                if (var_value)
                {
                    var_len = ft_strlen(var_value);
                    strncpy(result + j, var_value, var_len);
                    j += var_len;
                    free(var_value);
                }
                else
                {
                    result[j++] = '$';
                    strncpy(result + j, var_name, k);
                    j += k;
                }
            }

            free(var_name);
            i += k;
        }
        else
            result[j++] = token_value[i++];
    }
    result[j] = '\0';
    result = realloc(result, j + 1);
    return (result);
}

int should_combine_tokens(token_t *current_token, token_t *next_token) {
    if (!current_token || !next_token) {
        return 0; // Safety check
    }

    // Logic to decide if tokens should be combined
    if ((current_token->type == T_SINGLE_QUOTE || current_token->type == T_DOUBLE_QUOTE) &&
        (next_token->type == T_SINGLE_QUOTE || next_token->type == T_DOUBLE_QUOTE)) {
        return 1;
    }

    return 0;
}

char *combine_token_values(char *value1, char *value2) {
    size_t new_size = strlen(value1) + strlen(value2) + 1;
    char *combined_value = (char *)malloc(new_size);
    if (!combined_value) {
        perror("Memory Allocation Failed");
        return NULL;
    }

    strcpy(combined_value, value1);
    strcat(combined_value, value2);

    return combined_value;
}

void merge_connected_tokens(data_t *data)
{
    if (data == NULL || data->tokens == NULL)
        return;

    token_t *current = data->tokens;
    while (current != NULL && current->next != NULL)
    {
        if (current->connect == 1)
        {
            // Calculating the length for the merged string
            size_t merged_length = strlen(current->value) + strlen(current->next->value);
            char *merged_value = (char *)malloc(merged_length + 1); // +1 for the null terminator
            if (merged_value == NULL)
            {
                // Handle memory allocation failure
                perror("Memory allocation failed");
                return;
            }

            // Merging current token with the next
            strcpy(merged_value, current->value);
            strcat(merged_value, current->next->value);

            // Update the current token value
            free(current->value);
            current->value = merged_value;

            // Remove the next token and link the list
            token_t *to_remove = current->next;
            current->next = current->next->next;
            current->connect = to_remove->connect; // Transfer connect flag from the next token

            // Free the removed token
            free(to_remove->value);
            free(to_remove);
        }
        else
        {
            current = current->next;
        }
    }
}

void ms_expander(data_t *data)
{
    token_t *current_token;
    token_t *prev_token;
	t_quote_vars	vars;

    current_token = data->tokens;
    prev_token = NULL;


    while (current_token)
    {
        current_token->value = ms_clean_quotes(&vars, current_token->value);
        
        // if (current_token->type == T_TILDE)
        // {
        //     current_token->value = expand_tilde(data, current_token->value);
        //     current_token->type = T_WORD;
        // }
        if (current_token->type == T_WORD || current_token->type == T_DOUBLE_QUOTE)
        {            
            char *expanded_value = NULL;

            if (current_token->type == T_WORD)
            {
                if (strchr(current_token->value, '~'))
                {
                    current_token->value = expand_tilde(data, current_token->value);
                } 
            }

            if (strchr(current_token->value, '$'))
            {
                expanded_value = expand_quotes(data, current_token->value);
                current_token->value = expanded_value;
            }
        }

        if (current_token->value && strcmp(current_token->value, "") == 0) {
            token_t *next_token = current_token->next;
            remove_token(&(data->tokens), prev_token, current_token);
            
            if (prev_token == NULL) {
                current_token = data->tokens;
            } else {
                current_token = next_token;
            }
            continue;
        }

        if (current_token->type == T_SINGLE_QUOTE || current_token->type == T_DOUBLE_QUOTE)
            current_token->type = T_WORD;
        
        prev_token = current_token;
        current_token = current_token->next;
    }
    merge_connected_tokens(data);

    // print_list(data->tokens);
}
