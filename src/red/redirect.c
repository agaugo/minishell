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

void ms_redirect_in_from_token(data_t *data, token_t *start_token)
{
    int fd;
    token_t *token = start_token;

    while (token && token->type != T_REDIRECT_IN)
        token = token->next;
    if (!token || !token->next)
    {
        perror("Syntax Error");
        return;
    }
    fd = open(token->next->value, O_RDONLY);
    if (fd == -1)
    {
        perror("Error opening file");
        return;
    }

    if (dup2(fd, 0) == -1)
    {
        perror("Error duplicating fd");
        close(fd);
        return;
    }
    data->tokens->fd = fd;
}

void ms_redirect_out_from_token(data_t *data, token_t *start_token)
{
    int fd;
    token_t *token = start_token;

    while (token && token->type != T_REDIRECT_OUT)
        token = token->next;
    if (!token || !token->next)
    {
        perror("Syntax Error");
        return;
    }
    fd = open(token->next->value, O_WRONLY | O_CREAT | O_TRUNC, 0666);
    if (fd == -1)
    {
        perror("Error opening/creating file");
        return;
    }
    if (dup2(fd, 1) == -1)
    {
        perror("Error duplicating fd");
        close(fd);
        return;
    }
    data->tokens->fd = fd;
}

void  ms_redirect_out_append_from_token(data_t *data, token_t *start_token)
{
    int fd;
    token_t *token;

    token = start_token;
    while (token && token->type != T_APPEND_OUT)
        token = token->next;
    if (!token || !token->next)
    {
        perror("Syntax Error");
        return;
    }
    fd = open(token->next->value, O_WRONLY | O_CREAT | O_APPEND, 0666);
    if (fd == -1)
    {
        perror("Error opening/creating file");
        return ;
    }
    if (dup2(fd, 1) == -1)
    {
        perror("Error duplicating fd");
        close(fd);
        return ;
    }
    data->tokens->fd = fd;
}

void ms_redirect(data_t *data)
{
    token_t *token = data->tokens;

    while (token)
    {
        if (token->type == T_REDIRECT_OUT)
        {
            ms_redirect_out_from_token(data, token);
            token = token->next;  // Skip over the filename token
        }
        else if (token->type == T_REDIRECT_IN)
        {
            ms_redirect_in_from_token(data, token);
            token = token->next;  // Skip over the filename token
        }
        else if (token->type == T_APPEND_OUT)
        {
            ms_redirect_out_append_from_token(data, token);
            token = token->next;  // Skip over the filename token
        }
        if (token)
            token = token->next;  // Move to the next token
    }
}
