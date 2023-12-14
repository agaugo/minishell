/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   exe_redirects.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: trstn4 <trstn4@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/08/21 19:24:57 by trstn4        #+#    #+#                 */
/*   Updated: 2023/12/14 17:05:05 by trstn4        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ms_open_in(t_token_t *current)
{
	int		flags;
	int		fd;
	char	*error_msg;

	if (access(current->next->value, F_OK) == -1)
	{
		error_msg = ft_strjoin_free(ft_strdup(current->next->value),
				ft_strdup(": No such file or directory"));
		ft_putendl_fd(error_msg, STDERR);
		free_memory(error_msg);
		return (-1);
	}
	flags = O_RDONLY;
	fd = open(current->next->value, flags);
	if (fd == -1)
	{
		perror("open");
		return (-1);
	}
	dup2(fd, STDIN_FILENO);
	close(fd);
	return (0);
}

int	ms_open_out(t_token_t *current)
{
	int	flags;
	int	fd;

	if (current->type == T_APPEND_OUT)
		flags = O_WRONLY | O_CREAT | O_APPEND;
	else
		flags = O_WRONLY | O_CREAT | O_TRUNC;
	fd = open(current->next->value, flags, 0666);
	if (fd == -1)
	{
		perror("open");
		return (-1);
	}
	dup2(fd, STDOUT_FILENO);
	close(fd);
	return (0);
}

int	ms_setup_redirection(t_token_t *tokens)
{
	t_token_t	*current;

	current = tokens;
	while (current != NULL)
	{
		if (current->type == T_REDIRECT_IN && current->next->type == T_WORD)
		{
			if (ms_open_in(current) == -1)
				return (-1);
		}
		else if (current->type == T_REDIRECT_OUT
			|| current->type == T_APPEND_OUT)
		{
			if (ms_open_out(current) == -1)
				return (-1);
		}
		current = current->next;
	}
	return (0);
}

t_token_t	*ms_check_redirects(t_exec_t_data *cmd_data, t_token_t *cmd)
{
	while (cmd != NULL)
	{
		if (cmd->type == T_PIPE)
		{
			cmd_data->is_pipe = 1;
			break ;
		}
		if (cmd->type == T_REDIRECT_OUT || cmd->type == T_APPEND_OUT
			|| cmd->type == T_REDIRECT_IN)
			cmd_data->is_redirect = 1;
		cmd = cmd->next;
	}
	return (cmd);
}
