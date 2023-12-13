/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   echo_helper1.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: trstn4 <trstn4@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/23 00:11:40 by trstn4        #+#    #+#                 */
/*   Updated: 2023/12/13 16:06:05 by trstn4        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	open_error(t_data *data)
{
	perror("open");
	data->last_exit_code = 1;
	return ;
}

t_token_t	*set_token(t_token_t *token)
{
	if (token->next)
		token = token->next->next;
	else
		token = NULL;
	return (token);
}

void	restore_and_close(int flag_n, int stdout_backup, t_data *data)
{
	if (!flag_n)
		printf("\n");
	dup2(stdout_backup, STDOUT_FILENO);
	close(stdout_backup);
	data->last_exit_code = 0;
}

void	dup_and_close(int fd)
{
	dup2(fd, STDOUT_FILENO);
	close(fd);
}

void	should_print_space_func(int *should_print_space, t_token_t *token)
{
	if (*should_print_space)
		printf(" ");
	printf("%s", token->value);
	*should_print_space = 1;
}
