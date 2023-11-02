/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   echo.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: trstn4 <trstn4@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/23 00:11:40 by trstn4        #+#    #+#                 */
/*   Updated: 2023/11/02 12:40:58 by trstn4        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char *clean_quotes(const char *str)
{
    char *cleaned_str = malloc(strlen(str) + 1);
    size_t i = 0, j = 0;
    int in_single_quote = 0;
    int in_double_quote = 0;

    while (str[i])
    {
        if (str[i] == '\'' && !in_double_quote && (i == 0 || str[i - 1] != '\\' || (i > 1 && str[i - 2] == '\\')))
        {
            in_single_quote = !in_single_quote;
            i++;
        }
        else if (str[i] == '\"' && !in_single_quote && (i == 0 || str[i - 1] != '\\' || (i > 1 && str[i - 2] == '\\')))
        {
            in_double_quote = !in_double_quote;
            i++;
        }
        else if ((str[i] == '\'' || str[i] == '\"') && !in_single_quote && !in_double_quote &&
                 (i == 0 || i == strlen(str) - 1 || str[i - 1] == ' ' || str[i + 1] == ' ' || str[i + 1] == '\0'))
        {
            i++;
        }
        else if (str[i] == '\'' && str[i - 1] != ' ' && str[i + 1] != ' ' && !in_single_quote && !in_double_quote)
        {
            i++;
        }
        else if (str[i] == '\"' && str[i - 1] != ' ' && str[i + 1] == '\"' && !in_single_quote && !in_double_quote)
        {
            i += 2;
        }
        else
            cleaned_str[j++] = str[i++];
    }
    cleaned_str[j] = '\0';
    return cleaned_str;
}

// The rest of the code remains the same

void ms_echo_command(data_t *data, token_t *parsed_token)
{
    char *str = NULL;
    char *cleaned_str;
    token_t *token = parsed_token;

    while (token)
    {
        cleaned_str = clean_quotes(token->value);  // Clean quotes from token value
        if(str == NULL) 
            str = cleaned_str;
        else {
            char *temp = ft_strjoin(str, " ");
            free(str);
            str = ft_strjoin(temp, cleaned_str);
            free(temp);
            free(cleaned_str);
        }
        token = token->next;
    }

    if (data->tokens->next == NULL || data->tokens->next->value == NULL)
        printf("\n");
    else
    {
        if (ft_strcmp(data->tokens->next->value, "-n") == 0)
        {
            if (data->tokens->next->next && data->tokens->next->next->value)
            {
                char *value = data->tokens->next->next->value;
                int len = ft_strlen(value);
                while (len > 0 && value[len - 1] == '\n')
                {
                    value[len - 1] = '\0';
                    len--;
                }
                printf("%s", value);
            }
        }
        else
            printf("%s\n", str);
    }
    free(str);
}
