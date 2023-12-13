/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   echo.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: trstn4 <trstn4@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/23 00:11:40 by trstn4        #+#    #+#                 */
/*   Updated: 2023/12/13 13:30:06 by trstn4        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void ms_echo_command(data_t *data, token_t *token)
{
	int flag_n = 0;
	int first_word = 1;
	int stdout_backup = dup(STDOUT_FILENO);
	int should_print_space = 0;

	token = token->next;
	while (token)
	{
		if (token->type == T_PIPE)
			break ;
		if (first_word && ft_strcmp(token->value, "-n") == 0)
		{
			flag_n = 1;
			token = token->next;
			continue ;
		}
		first_word = 0;
		if (token->type == T_REDIRECT_OUT || token->type == T_APPEND_OUT)
		{
			int flags = (token->type == T_APPEND_OUT) ? (O_WRONLY | O_CREAT | O_APPEND) : (O_WRONLY | O_CREAT | O_TRUNC);
			token = token->next;
			if (token && token->value)
			{
				int fd = open(token->value, flags, 0666);
				if (fd < 0)
				{
					perror("open");
					data->last_exit_code = 1;
					return ;
				}
				dup2(fd, STDOUT_FILENO);
				close(fd);
				token = token->next;
				continue ;
			}
		}
		if (token->type == T_REDIRECT_IN)
		{
			token = token->next ? token->next->next : NULL;
			continue ;
		}
		if (token && token->type == T_WORD)
		{
			if (should_print_space)
				printf(" ");
			printf("%s", token->value);
			should_print_space = 1;
		}
		token = token->next;
	}
	if (!flag_n)
		printf("\n");
	dup2(stdout_backup, STDOUT_FILENO);
	close(stdout_backup);
	data->last_exit_code = 0;
}
