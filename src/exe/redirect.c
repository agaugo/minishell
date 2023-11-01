/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   redirect.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: trstn4 <trstn4@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/08/21 19:24:57 by trstn4        #+#    #+#                 */
/*   Updated: 2023/11/01 15:33:41 by trstn4        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

//void  ms_redirect_in(data_t data)
//{
//    if (!data.tokens)
//        perror("Syntax Error");
//}

void  ms_redirect_out(data_t *data)
{
    int fd;
    token_t *token;

    token = data->tokens;
    while (token->type != T_REDIRECT_OUT)
        token = token->next;
    if (!token->next) {
        perror("Syntax Error");
        return;
    }
    fd = open(token->next->value, O_WRONLY | O_CREAT | O_TRUNC, 0666);
    if (fd == -1) {
        perror("Error opening/creating file");
        return ;
    }
    if (dup2(fd, 1) == -1) {
        perror("Error duplicating fd");
        close(fd);
    }
    data->tokens->fd = fd;
}

void ms_redirect(data_t *data)
{
//    if (data.tokens->next->type == T_REDIRECT_IN)
//        ms_redirect_in(data);
    token_t *token;

    token = data->tokens;
    while (token->next != NULL)
    {
        if (token->next->type == T_REDIRECT_OUT)
            ms_redirect_out(data);
        if (token->next->type == T_APPEND_OUT)
            ms_redirect_out_append(data);
        token = token->next;
    }
}