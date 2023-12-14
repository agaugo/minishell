/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   echo.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: trstn4 <trstn4@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/23 00:11:40 by trstn4        #+#    #+#                 */
/*   Updated: 2023/12/14 15:55:02 by trstn4        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_token_t	*ms_echo_print(t_echo_data *echo_data, t_token_t *token)
{
	if (token && token->type == T_WORD)
	{
		if (echo_data->should_print_space)
			printf(" ");
		printf("%s", token->value);
		echo_data->should_print_space = 1;
	}
	return (token->next);
}

int	ms_echo_redirect(t_data *data, t_echo_data *echo_data, t_token_t **token)
{
	int	flags;

	if ((*token)->type == T_REDIRECT_OUT || (*token)->type == T_APPEND_OUT)
	{
		if ((*token)->type == T_APPEND_OUT)
			flags = O_WRONLY | O_CREAT | O_APPEND;
		else
			flags = O_WRONLY | O_CREAT | O_TRUNC;
		*token = (*token)->next;
		if (*token && (*token)->value)
		{
			echo_data->fd = open((*token)->value, flags, 0666);
			if (echo_data->fd < 0)
			{
				perror("open");
				data->last_exit_code = 1;
				return (2);
			}
			dup2(echo_data->fd, STDOUT_FILENO);
			close(echo_data->fd);
			*token = (*token)->next;
			return (1);
		}
	}
	return (0);
}

int	ms_echo_redirect_in(t_echo_data *echo_data, t_token_t **token)
{
	if ((*token)->type == T_REDIRECT_IN)
	{
		if ((*token)->next != NULL)
			*token = (*token)->next->next;
		else
			*token = NULL;
		return (1);
	}
	*token = ms_echo_print(echo_data, (*token));
	return (0);
}

int	ms_echo_handler(t_data *data, t_echo_data *echo_data, t_token_t **token)
{
	int	status;

	if (echo_data->first_word && ft_strcmp((*token)->value, "-n") == 0)
	{
		echo_data->flag_n = 1;
		*token = (*token)->next;
		return (1);
	}
	echo_data->first_word = 0;
	status = ms_echo_redirect(data, echo_data, token);
	if (status == 1)
		return (1);
	else if (status == 2)
		return (2);
	if (ms_echo_redirect_in(echo_data, token) == 1)
		return (1);
	return (0);
}

void	ms_echo_command(t_data *data, t_token_t *token)
{
	t_echo_data	echo_data;
	int			status;

	echo_data.flag_n = 0;
	echo_data.first_word = 1;
	echo_data.stdout_backup = dup(STDOUT_FILENO);
	echo_data.should_print_space = 0;
	token = token->next;
	while (token)
	{
		if (token->type == T_PIPE)
			break ;
		status = ms_echo_handler(data, &echo_data, &token);
		if (status == 1)
			continue ;
		else if (status == 2)
			return ;
	}
	if (!echo_data.flag_n)
		printf("\n");
	dup2(echo_data.stdout_backup, STDOUT_FILENO);
	close(echo_data.stdout_backup);
	data->last_exit_code = 0;
}
