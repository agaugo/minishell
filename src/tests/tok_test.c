/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   tok_test.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: trstn4 <trstn4@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/09/21 13:42:34 by trstn4        #+#    #+#                 */
/*   Updated: 2023/12/12 17:02:13 by trstn4        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	test_tok(token_t *head)
{
	token_t	*current_token;
	int		i;

	current_token = head;
	i = 0;
	printf("----------- tokenizer debug ----------------------------------\n");
	while (current_token)
	{
		printf("Token %d: %s, Type: %d, Connect: %i\n", i, current_token->value,
			current_token->type, current_token->connect);
		current_token = current_token->next;
		i++;
	}
	printf("--------------------------------------------------------------\n");
}
