/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   echo.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: trstn4 <trstn4@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/23 00:11:40 by trstn4        #+#    #+#                 */
/*   Updated: 2023/10/25 11:15:37 by trstn4        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void ms_echo_command(token_t *token)
{
    if (token->next == NULL || token->next->value == NULL)
        printf("\n");
    else
    {
        if (strcmp(token->next->value, "-n") == 0)
        {
            if (token->next->next && token->next->next->value)
            {
                char *value = token->next->next->value;
                int len = strlen(value);
                
                while (len > 0 && value[len - 1] == '\n')
                {
                    value[len - 1] = '\0';
                    len--;
                }

                printf("%s", value);
            }
        }
        else
            printf("%s\n", token->next->value);
    }
}

