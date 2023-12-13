/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   tok_utils.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: trstn4 <trstn4@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/09/21 13:42:34 by trstn4        #+#    #+#                 */
/*   Updated: 2023/12/12 17:51:14 by trstn4        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ms_is_whitespace(char c)
{
	return (c == ' ' || c == '\t');
}

token_t	*init_new_token(char *start, char *current, tokentype_t type)
{
	token_t	*new_token;

	new_token = allocate_memory(sizeof(token_t));
	new_token->value = ft_strndup(start, current - start);
	new_token->type = type;
	new_token->next = NULL;
	new_token->connect = 0;
	return (new_token);
}
