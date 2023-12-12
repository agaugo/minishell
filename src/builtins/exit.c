/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   exit.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: trstn4 <trstn4@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/08/25 10:37:37 by trstn4        #+#    #+#                 */
/*   Updated: 2023/12/12 11:53:42 by trstn4        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ms_str_isdigit(const char *str)
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

static void	ms_check_args_and_exit(data_t *data, token_t *token)
{
	int	exit_code;

	if (ms_str_isdigit(token->value) == 0)
	{
		fprintf(stderr, "exit: %s: numeric argument required\n", token->value);
		wipe_data_struct(data);
		exit(255);
	}
	exit_code = ft_atoi(token->value);
	printf("exit\n");
	wipe_data_struct(data);
	exit(exit_code % 256);
}

void	ms_exit_shell(data_t *data, token_t *token)
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
		fprintf(stderr, "exit: too many arguments\n");
		data->last_exit_code = 1;
		return ;
	}
	ms_check_args_and_exit(data, token);
}
