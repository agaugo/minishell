/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   exit.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: trstn4 <trstn4@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/08/25 10:37:37 by trstn4        #+#    #+#                 */
/*   Updated: 2023/12/14 01:06:29 by trstn4        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	ms_str_isdigit(const char *str)
{
	if (str == NULL)
		return (0);
	if (*str == '-' || *str == '+')
		str++;
	while (*str != '\0')
	{
		if (*str < '0' || *str > '9')
			return (0);
		else
			str++;
	}
	return (1);
}

static void	ms_check_args_and_exit(t_data *data, t_token_t *token)
{
	int	exit_code;

	if (ms_str_isdigit(token->value) == 0)
	{
		ft_putendl_fd("minishell: numeric argument required", STDERR);
		wipe_data_struct(data);
		exit(2);
	}
	exit_code = ft_atoi(token->value);
	printf("exit\n");
	wipe_data_struct(data);
	exit(exit_code % 256);
}

void	ms_exit_shell(t_data *data, t_token_t *token)
{
	if (!token)
	{
		printf("exit\n");
		wipe_data_struct(data);
		exit(0);
	}
	if (token->type == T_WORD && token->next
		&& token->next->type == T_WORD)
	{
		ft_putendl_fd("minishell: too many arguments", STDERR);
		data->last_exit_code = 1;
		return ;
	}
	ms_check_args_and_exit(data, token);
}
