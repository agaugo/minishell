/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   echo_helper2.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: trstn4 <trstn4@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/23 00:11:40 by trstn4        #+#    #+#                 */
/*   Updated: 2023/12/13 16:10:53 by trstn4        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_token_t	*if_body1(t_token_t *token, int *flags)
{
	fill_flag(token, flags);
	token = token->next;
	return (token);
}

t_token_t	*if_body2(int *fd, t_token_t *token, int *flags, t_data *data)
{
	*fd = open(token->value, *flags, 0666);
	if (*fd < 0)
	{
		open_error(data);
		return (token);
	}
	dup_and_close(*fd);
	token = token->next;
	return (token);
}

t_token_t	*type_append_or_out(t_token_t *token, int *flags, t_data *data,
				int *fd)
{
	if_body1(token, flags);
	if (token && token->value)
		token = if_body2(fd, token, flags, data);
	return (token);
}

t_token_t	*big_mama(t_token_t *token, t_data *data, t_echo_t_data *echo_data)
{
	if (token->type == T_REDIRECT_OUT || token->type == T_APPEND_OUT)
		token = type_append_or_out(token, &echo_data->flags, data,
				&echo_data->fd);
	else if (token && token->type == T_WORD)
		should_print_space_func(&echo_data->should_print_space, token);
	return (token->next);
}

t_token_t	*assign_flag_n(t_token_t *token, int *flag_n)
{
	*flag_n = 1;
	token = token->next;
	return (token);
}
