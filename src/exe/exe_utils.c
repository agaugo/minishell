/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   exe_utils.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: trstn4 <trstn4@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/08/21 19:24:57 by trstn4        #+#    #+#                 */
/*   Updated: 2023/12/13 19:07:59 by trstn4        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	**ms_get_full_args(t_token_t *start_token, t_token_t *end_token)
{
	int			arg_count;
	char		**args;
	t_token_t	*current;
	int			i;

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

void	ms_throw_error(t_data *data, t_token_t *current)
{
	char	*error_msg;

	if (current->status == 126)
	{
		error_msg = ft_strjoin_free(ft_strdup(current->value),
				ft_strdup(": Is a directory"));
		ft_putendl_fd(error_msg, STDERR);
		free_memory(error_msg);
		data->last_exit_code = 126;
		exit(126);
	}
	if (current->status == 127)
	{
		error_msg = ft_strjoin_free(ft_strdup(current->value),
				ft_strdup(": command not found"));
		ft_putendl_fd(error_msg, STDERR);
		free_memory(error_msg);
		data->last_exit_code = 127;
		exit(127);
	}
}
