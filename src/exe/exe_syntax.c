/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   exe_syntax.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: trstn4 <trstn4@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/08/21 19:24:57 by trstn4        #+#    #+#                 */
/*   Updated: 2023/12/14 17:05:58 by trstn4        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ms_exe_check_syntax_pipe(t_data *data, t_token_t *cmd, t_token_t *prev_cmd)
{
	char	*error_msg;

	if (cmd->next == NULL || cmd == NULL || prev_cmd->type != T_WORD)
	{
		error_msg = ft_strjoin_free(
				ft_strdup("syntax error near unexpected token '"),
				ft_strdup("|'"));
		ft_putendl_fd(error_msg, STDERR);
		free_memory(error_msg);
		data->last_exit_code = 258;
		return (1);
	}
	return (0);
}

int	ms_exe_check_syntax_redirects(t_data *data, t_token_t *cmd)
{
	char	*syntax_token_value;
	char	*error_msg;

	if (cmd->next == NULL
		|| (cmd->next && cmd->next->type != T_WORD))
	{
		if (cmd->next == NULL)
			syntax_token_value = "newline";
		else
			syntax_token_value = cmd->next->value;
		error_msg = ft_strjoin_free(
				ft_strdup("syntax error near unexpected token '"),
				ft_strdup(syntax_token_value));
		error_msg = ft_strjoin_free(error_msg, ft_strdup("'"));
		ft_putendl_fd(error_msg, STDERR);
		free_memory(error_msg);
		data->last_exit_code = 258;
		return (1);
	}
	return (0);
}

int	ms_exe_check_syntax(t_data *data)
{
	t_token_t	*cmd;
	t_token_t	*prev_cmd;

	cmd = data->tokens;
	prev_cmd = NULL;
	while (cmd != NULL)
	{
		if (cmd->type == T_PIPE)
		{
			if (ms_exe_check_syntax_pipe(data, cmd, prev_cmd) == 1)
				return (1);
		}
		if (cmd->type == T_REDIRECT_OUT || cmd->type == T_APPEND_OUT
			|| cmd->type == T_REDIRECT_IN || cmd->type == T_HEREDOC)
		{
			if (ms_exe_check_syntax_redirects(data, cmd) == 1)
				return (1);
		}
		prev_cmd = cmd;
		cmd = cmd->next;
	}
	return (0);
}
