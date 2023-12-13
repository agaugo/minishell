/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   exe_utils.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: trstn4 <trstn4@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/08/21 19:24:57 by trstn4        #+#    #+#                 */
/*   Updated: 2023/12/13 08:52:57 by trstn4        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	**ms_get_full_args(token_t *start_token, token_t *end_token)
{
	int		arg_count;
	char	**args;
	token_t	*current;
	int		i;

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
	i = 0;
	while (i < arg_count)
	{
		if (current->type == T_REDIRECT_OUT)
			break ;
		args[i++] = ft_strdup(current->value);
		current = current->next;
	}
	args[arg_count] = NULL;
	return (args);
}

void	ms_throw_error(data_t *data, token_t *current)
{
	if (current->status == 126)
	{
		fprintf(stderr, "%s: is a directory\n", current->value);
		data->last_exit_code = 126;
		exit(126);
	}
	if (current->status == 127)
	{
		fprintf(stderr, "%s: command not found\n", current->value);
		data->last_exit_code = 127;
		exit(127);
	}
}
