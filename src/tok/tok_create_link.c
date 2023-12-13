/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   tok_create_link.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: trstn4 <trstn4@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/09/21 13:42:34 by trstn4        #+#    #+#                 */
/*   Updated: 2023/12/12 17:56:42 by trstn4        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	parse_special_tokens(char **current, token_t **head,
			token_t **current_token)
{
	char		*start;
	tokentype_t	type;
	char		*value;
	token_t		*new_token;

	start = *current;
	type = T_WORD;
	if (**current == '|')
		type = parse_pipe_token(current);
	else
		type = parse_redirect_token(current);
	value = ft_strndup(start, *current - start);
	new_token = init_new_token(value, *current, type);
	free_memory(value);
	if (!*head)
		*head = new_token;
	else
		(*current_token)->next = new_token;
	*current_token = new_token;
	(*current_token)->connect = 0;
}

void	parse_regular_tokens(char **current, token_t **head,
			token_t **current_token)
{
	char		*start;
	tokentype_t	type;
	char		*value;
	token_t		*new_token;

	start = *current;
	if (**current == '\'' || **current == '\"')
		type = parse_quote_token(current);
	else
		type = parse_word_token(current);
	if (*current != start)
	{
		value = ft_strndup(start, *current - start);
		new_token = init_new_token(value, *current, type);
		free_memory(value);
		if (!*head)
			*head = new_token;
		else
			(*current_token)->next = new_token;
		*current_token = new_token;
		(*current_token)->connect = !(ms_is_whitespace(**current)
				|| **current == '|' || **current == '<' || **current == '>');
	}
}
