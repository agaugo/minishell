/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   expander.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: trstn4 <trstn4@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/08/21 19:24:57 by trstn4        #+#    #+#                 */
/*   Updated: 2023/12/12 20:48:00 by trstn4        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char *expand_tilde(data_t *data, char *token_value)
{
    if (token_value[0] == '~' && (token_value[1] == '/' || token_value[1] == '\0')) {
        int home_index = ms_find_env_index(data->envp, "HOME");
        if (home_index == -1) {
            perror("Environment Variable HOME Not Found");
            return ft_strdup(token_value);
        }
        char *home_path = ft_strchr(data->envp[home_index], '=') + 1;
        size_t new_size = ft_strlen(home_path) + strlen(token_value);
        char *new_token_value = (char *)allocate_memory(new_size);
        if (new_token_value == NULL) {
            perror("Memory Allocation Failed");
            return ft_strdup(token_value);
        }
        ft_strcpy(new_token_value, home_path);
        ft_strcat(new_token_value, token_value + 1);

        return new_token_value;
    }
    return ft_strdup(token_value);
}

char *expand_dollarsign(data_t *data, char *token_value)
{
    data->last_exit_code = 0;
    int index = ms_find_env_index(data->envp, token_value);
    if (index == -1) {
        return ft_strdup("");
    }
    char *var_val = ft_strchr(data->envp[index], '=') + 1;
    return ft_strdup(var_val);
}

void remove_token(token_t **head, token_t *prev_token, token_t *current_token)
{
    if (!current_token) return;

    if (prev_token == NULL) {
        *head = current_token->next;
    } else {
        prev_token->next = current_token->next;
    }
    free_memory(current_token->value);
    free_memory(current_token);
}

char *expand_quotes(data_t *data, char *token_value)
{
    char *result;
    char *var_name;
    char *var_value;
    int i = 0, j = 0, k, var_len;
    int do_free = 0;

    result = allocate_memory(4096);
    if (!result)
        return NULL;
    
    while (token_value[i])
    {
        if (token_value[i] == '$' && token_value[i+1] == '?')
        {
            char *exit_code_str = ft_itoa(data->last_exit_code);
            size_t exit_code_len = ft_strlen(exit_code_str);
            char *new_token_value = (char *)allocate_memory(ft_strlen(token_value) + exit_code_len + 1);
            
            ft_strncpy(new_token_value, token_value, i);
            ft_strcpy(new_token_value + i, exit_code_str);
            ft_strcpy(new_token_value + i + exit_code_len, token_value + i + 2);
            free_memory(exit_code_str);
            do_free = 1;
            token_value = new_token_value;
        }
        if (token_value[i] == '$' && token_value[i + 1] != '\'')
        {
            i++;
            k = 0;
            var_name = (char *)allocate_memory(ft_strlen(token_value) + 1);
            ft_memset(var_name, 0, ft_strlen(token_value) + 1);
            while (ft_isalnum(token_value[i + k]) || token_value[i + k] == '_' || token_value[i + k] == '?')
            {
                var_name[k] = token_value[i + k];
                k++;
            }
            var_name[k] = '\0';
            if (k == 0)
            {
                result[j++] = '$';
            }
            else if (ft_strcmp(var_name, "?") == 0)
            {
                var_value = ft_itoa(data->last_exit_code);
                var_len = ft_strlen(var_value);
                ft_strncpy(result + j, var_value, var_len);
                j += var_len;
                free_memory(var_value);
            }
            else
            {
                var_value = expand_dollarsign(data, var_name);
                if (var_value)
                {
                    var_len = ft_strlen(var_value);
                    ft_strncpy(result + j, var_value, var_len);
                    j += var_len;
                    free_memory(var_value);
                }
                else
                {
                    result[j++] = '$';
                    ft_strncpy(result + j, var_name, k);
                    j += k;
                }
            }

            free_memory(var_name);
            i += k;
        }
        else
            result[j++] = token_value[i++];
    }
    result[j] = '\0';
    result = memory_realloc(result, j + 1);
    if (do_free)
        free(token_value);
    return (result);
}

int should_combine_tokens(token_t *current_token, token_t *next_token) {
    if (!current_token || !next_token) {
        return 0;
    }
    if ((current_token->type == T_SINGLE_QUOTE || current_token->type == T_DOUBLE_QUOTE) &&
        (next_token->type == T_SINGLE_QUOTE || next_token->type == T_DOUBLE_QUOTE)) {
        return 1;
    }
    return 0;
}

char *combine_token_values(char *value1, char *value2) {
    size_t new_size = ft_strlen(value1) + ft_strlen(value2) + 1;
    char *combined_value = (char *)allocate_memory(new_size);
    ft_strcpy(combined_value, value1);
    ft_strcat(combined_value, value2);
    return combined_value;
}

char *merge_token_values(token_t *current, token_t *next)
{
    size_t merged_length = strlen(current->value) + strlen(next->value);
    char *merged_value = (char *)allocate_memory(merged_length + 1);

    strcpy(merged_value, current->value);
    strcat(merged_value, next->value);

    return merged_value;
}

void remove_next_token(token_t *current)
{
    token_t *to_remove = current->next;
    current->next = current->next->next;

    free_memory(to_remove->value);
    free_memory(to_remove);
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
            char *merged_value = merge_token_values(current, current->next);
            free_memory(current->value);
            current->value = merged_value;

            current->connect = current->next->connect;
            remove_next_token(current);
        }
        else
            current = current->next;
    }
}

void expand_variable(data_t *data, token_t *current_token)
{
    char *expanded_value = expand_quotes(data, current_token->value);
    free_memory(current_token->value);
    current_token->value = expanded_value;
}

void process_quotes(t_quote_vars *vars, token_t *current_token)
{
    char *cq = ms_clean_quotes(vars, current_token->value);
    free_memory(current_token->value);
    current_token->value = cq;
}

void expand_tokens(data_t *data, token_t *current_token)
{
    if (ft_strchr(current_token->value, '~'))
    {
        char *et = expand_tilde(data, current_token->value);
        free_memory(current_token->value);
        current_token->value = et;
    }
    if (ft_strchr(current_token->value, '$'))
    {
        char *ev = expand_quotes(data, current_token->value);
        free_memory(current_token->value);
        current_token->value = ev;
    }
}

void update_token_type(token_t *current_token)
{
    if (current_token->type == T_SINGLE_QUOTE || current_token->type == T_DOUBLE_QUOTE)
        current_token->type = T_WORD;
}

void remove_empty_token(data_t *data, token_t **prev_token, token_t **current_token)
{
    if (*current_token && strcmp((*current_token)->value, "") == 0)
    {
        token_t *next_token = (*current_token)->next;
        remove_token(&(data->tokens), *prev_token, *current_token);
        
        if (*prev_token == NULL)
            *current_token = data->tokens;
        else
            *current_token = next_token;
    }
}

void ms_expander(data_t *data)
{
    token_t *current_token = data->tokens;
    token_t *prev_token = NULL;
    t_quote_vars	vars;

    while (current_token)
    {
        process_quotes(&vars, current_token);
        if (current_token->type == T_WORD || current_token->type == T_DOUBLE_QUOTE)
        {
            if (current_token->type == T_WORD)
                expand_tokens(data, current_token);
        }
        if (current_token->type == T_DOUBLE_QUOTE)
            expand_variable(data, current_token);
        remove_empty_token(data, &prev_token, &current_token);
        if (!current_token)
            continue;
        update_token_type(current_token);
        prev_token = current_token;
        current_token = current_token->next;
    }
    merge_connected_tokens(data);
}
