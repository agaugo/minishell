/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   test.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: trstn4 <trstn4@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/09/21 13:42:34 by trstn4        #+#    #+#                 */
/*   Updated: 2023/12/13 15:11:58 by trstn4        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	test_print(t_token_t *head)
{
	t_token_t	*current_token;
	int			i;

	i = 0;
	current_token = head;
	printf("--------------------- debug ----------------------------------\n");
	while (current_token)
	{
		printf("Token %d: %s, Type: %d, Connect: %i\n", i, current_token->value,
			current_token->type, current_token->connect);
		current_token = current_token->next;
		i++;
	}
	printf("--------------------------------------------------------------\n");
}
