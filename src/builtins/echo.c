/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   echo.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: trstn4 <trstn4@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/23 00:11:40 by trstn4        #+#    #+#                 */
/*   Updated: 2023/12/13 16:08:20 by trstn4        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	fill_flag(t_token_t *token, int *flags)
{
	if (token->type == T_APPEND_OUT)
		*flags = O_WRONLY | O_CREAT | O_APPEND;
	else
		*flags = O_WRONLY | O_CREAT | O_TRUNC;
}

void	assign_struct(t_echo_t_data *echo_data)
{
	echo_data->flag_n = 0;
	echo_data->first_word = 1;
	echo_data->stdout_backup = dup(STDOUT_FILENO);
	echo_data->should_print_space = 0;
}

void	ms_echo_command(t_data *data, t_token_t *token)
{
	t_echo_t_data	echo_data;

	assign_struct(&echo_data);
	token = token->next;
	while (token)
	{
		if (token->type == T_PIPE)
			break ;
		if (echo_data.first_word)
		{
			if (ft_strcmp(token->value, "-n") == 0)
			{
				token = (assign_flag_n(token, &echo_data.flag_n));
				continue ;
			}
			echo_data.first_word = 0;
		}
		if (token->type == T_REDIRECT_IN)
		{
			token = set_token(token);
			continue ;
		}
		token = big_mama(token, data, &echo_data);
	}
	restore_and_close(echo_data.flag_n, echo_data.stdout_backup, data);
	exit(0);
}
