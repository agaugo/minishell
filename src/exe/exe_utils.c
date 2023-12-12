/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   exe_utils.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: trstn4 <trstn4@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/08/21 19:24:57 by trstn4        #+#    #+#                 */
/*   Updated: 2023/12/12 23:23:43 by trstn4        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	**ms_get_full_args(token_t *start_token, token_t *end_token)
{
	int		arg_count;
	char	**args;
	token_t	*current;

	current = start_token;
	arg_count = 0;
	while (current != end_token && current->type != T_REDIRECT_OUT
		&& current->type != T_APPEND_OUT && current->type != T_REDIRECT_IN)
	{
		arg_count++;
		current = current->next;
	}
	args = (char **)allocate_memory((arg_count + 1) * sizeof(char *));
	current = start_token;
	for (int i = 0; i < arg_count; i++)
	{
		if (current->type == T_REDIRECT_OUT)
		{
			break ;
		}
		args[i] = ft_strdup(current->value);
		current = current->next;
	}
	args[arg_count] = NULL;
	return (args);
}
