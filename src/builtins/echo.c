/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   echo.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: trstn4 <trstn4@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/23 00:11:40 by trstn4        #+#    #+#                 */
/*   Updated: 2023/10/25 11:51:31 by trstn4        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void ms_echo_command(data_t *data)
{
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
            printf("%s\n", data->tokens->next->value);
    }
}

