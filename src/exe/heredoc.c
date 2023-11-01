/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   heredoc.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: trstn4 <trstn4@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/11/01 16:11:03 by trstn4        #+#    #+#                 */
/*   Updated: 2023/11/01 16:18:58 by trstn4        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ms_heredoc(token_t *token)
{
    char *delimiter = token->next->value;
    char *input;
    char *heredoc_content = NULL;
    while (1)
    {
        input = readline("heredoc> ");
        if (strcmp(input, delimiter) == 0)
        {
            free(input);
            break;
        }
		ft_strjoin(heredoc_content, input);
        free(input);
    }
	printf("%s\n", heredoc_content);
}