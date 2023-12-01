/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   expander.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: trstn4 <trstn4@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/08/21 19:24:57 by trstn4        #+#    #+#                 */
/*   Updated: 2023/12/01 18:17:19 by trstn4        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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
    int index = ms_find_env_index(data->envp, "HOME");
    if (index == -1) {
        perror("Environment Variable Not Found");
        return token_value;
    }
    char *var_val = strchr(data->envp[index], '=') + 1;
    return strdup(var_val);
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

void ms_expander(data_t *data)
{
    token_t *current_token;
    token_t *prev_token;

    current_token = data->tokens;
    prev_token = NULL;
    while (current_token)
    {
        if (current_token->type == T_TILDE)
        {
            current_token->value = expand_tilde(data, current_token->value);
            current_token->type = T_WORD;
        }
        else if (current_token->type == T_DOUBLE_QUOTE)
        {
            current_token->value = expand_quotes(data, current_token->value);
            current_token->type = T_WORD;
        }
        else if (current_token->type == T_WORD)
        {
            char *expanded_value = NULL;

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
        
        prev_token = current_token;
        current_token = current_token->next;
    }
    // print_list(data->tokens);
}
