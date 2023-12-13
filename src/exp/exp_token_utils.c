/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   exp_token_utils.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: trstn4 <trstn4@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/08/21 19:24:57 by trstn4        #+#    #+#                 */
/*   Updated: 2023/12/13 15:33:51 by trstn4        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	update_token_type(t_token_t *current_token)
{
	if (current_token->type == T_SINGLE_QUOTE
		|| current_token->type == T_DOUBLE_QUOTE)
		current_token->type = T_WORD;
}

void	remove_token(t_token_t **head, t_token_t *prev_token,
			t_token_t *current_token)
{
	if (!current_token)
		return ;
	if (prev_token == NULL)
		*head = current_token->next;
	else
		prev_token->next = current_token->next;
	free_memory(current_token->value);
	free_memory(current_token);
}

void	remove_empty_token(t_data *data, t_token_t **prev_token,
			t_token_t **current_token)
{
	t_token_t	*next_token;

	if (*current_token && ft_strcmp((*current_token)->value, "") == 0)
	{
		next_token = (*current_token)->next;
		remove_token(&(data->tokens), *prev_token, *current_token);
		if (*prev_token == NULL)
			*current_token = data->tokens;
		else
			*current_token = next_token;
	}
}

void	remove_next_token(t_token_t *current)
{
	t_token_t	*to_remove;

	to_remove = current->next;
	current->next = current->next->next;
	free_memory(to_remove->value);
	free_memory(to_remove);
}
