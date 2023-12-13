/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   tokenizer.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: trstn4 <trstn4@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/09/21 13:42:34 by trstn4        #+#    #+#                 */
/*   Updated: 2023/12/13 14:29:21 by trstn4        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

token_t	*ms_tokenizer(t_data data)
{
	token_t	*head;
	token_t	*current_token;
	char	*current;

	head = NULL;
	current_token = NULL;
	current = data.user_input;
	while (*current != '\0')
	{
		while (ms_is_whitespace(*current))
			current++;
		if (*current == '<' || *current == '>' || *current == '|')
			parse_special_tokens(&current, &head, &current_token);
		else
			parse_regular_tokens(&current, &head, &current_token);
	}
	return (head);
}
