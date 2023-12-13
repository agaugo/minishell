/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main_redirect.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: trstn4 <trstn4@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/08/21 19:24:57 by trstn4        #+#    #+#                 */
/*   Updated: 2023/12/13 15:07:01 by trstn4        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	ms_red_free(t_token_t *token, t_token_t	*tmp)
{
	free_memory(token->value);
	free_memory(token);
	free_memory(tmp->value);
	free_memory(tmp);
}

void	ms_check_redirect(t_data *data)
{
	t_token_t	*token;
	t_token_t	*prev;

	token = data->tokens->next;
	prev = data->tokens;
	while (token)
	{
		if (token->type == T_REDIRECT_OUT || token->type == T_APPEND_OUT)
			data->redirect = 1;
		else if (token->type == T_REDIRECT_IN)
			data->redirect = 2;
		else if (token->type == T_HEREDOC)
		{
			ms_heredoc(data, token);
			if (token->next)
			{
				prev->next = token->next->next;
				ms_red_free(token, token->next);
				token = prev->next;
				continue ;
			}
		}
		prev = token;
		token = token->next;
	}
}
