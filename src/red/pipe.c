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

//void ms_pipe(data_t *data)
//{
//    pipe(data->pipe);
//    if (fork() == 0) {
//        close(data->pipe[0]);        // Close unused read end
//        dup2(data->pipe[1], STDOUT_FILENO);  // Connect stdout to write end of pipe
//        close(data->pipe[1]); ;// Close the original file descriptor after duplicating
//    } else {
//        close(data->pipe[1]);        // Close unused write end
//        dup2(data->pipe[0], STDIN_FILENO);   // Connect stdin to read end of pipe
//        close(data->pipe[0]);        // Close the original file descriptor after duplicating
//    }
//    return ;
//}
//
//void ms_check_pipe(data_t *data) {
//    token_t *token;
//
//    token = data->tokens->next;
//    while (token != NULL)
//    {
//        if (token->type == T_PIPE)
//        {
//            ms_pipe(data);
//            data->redirect = 1;
//            return ;
//        }
//        token = token->next;
//    }
//    return ;
//
//}
