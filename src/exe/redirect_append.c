/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   redirect_append.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: trstn4 <trstn4@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/08/21 19:24:57 by trstn4        #+#    #+#                 */
/*   Updated: 2023/11/01 14:16:14 by trstn4        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void  ms_redirect_out_append(data_t *data)
{
    int fd;

    if (!data->tokens->next->next) {
        perror("Syntax Error");
        return;
    }
    // Changed O_TRUNC to O_APPEND
    printf("fwsfw");
    fd = open(data->tokens->next->next->value, O_WRONLY | O_CREAT | O_APPEND, 0666);
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
