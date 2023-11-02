/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   echo.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: trstn4 <trstn4@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/23 00:11:40 by trstn4        #+#    #+#                 */
/*   Updated: 2023/11/02 10:52:16 by trstn4        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void ms_echo_command(data_t *data, token_t *parsed_token)
{
    char *str;
    token_t *token;

    str = "";
    token = parsed_token;
    while (token)
    {
        // printf("READ\n");
        str = ft_strjoin(str, token->value);
        token = token->next;
        if (token)
            str = ft_strjoin(str, " ");
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
}

