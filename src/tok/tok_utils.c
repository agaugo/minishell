/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   tok_utils.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: trstn4 <trstn4@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/09/21 13:42:34 by trstn4        #+#    #+#                 */
/*   Updated: 2023/12/13 15:07:21 by trstn4        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ms_is_whitespace(char c)
{
	return (c == ' ' || c == '\t');
}

t_token_t	*init_new_token(char *start, char *current, t_tokentype_t type)
{
	t_token_t	*new_token;

	new_token = allocate_memory(sizeof(t_token_t));
	new_token->value = ft_strndup(start, current - start);
	new_token->type = type;
	new_token->next = NULL;
	new_token->connect = 0;
	return (new_token);
}
