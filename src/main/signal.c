/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   signal.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: trstn4 <trstn4@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/24 23:57:59 by trstn4        #+#    #+#                 */
/*   Updated: 2023/12/14 19:38:57 by trstn4        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	g_print_new_prompt;

void	ms_handle_ctrl_c(int _signalNumber)
{
	if (g_print_new_prompt == 0)
	{
		(void)_signalNumber;
		printf("\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
	else
		printf("\n");
}

void	ms_handle_ctrl_d(t_data *data)
{
	if (!data->user_input)
	{
		printf("exit\n");
		exit(0);
	}
}

void	ms_handle_ctrl_backspace(int _signalNumber)
{
	(void)_signalNumber;
}

int	ms_init_signals(void)
{
	g_print_new_prompt = 0;
	if (signal(SIGINT, ms_handle_ctrl_c) == SIG_ERR
		|| signal(SIGQUIT, SIG_IGN) == SIG_ERR)
		ms_handle_error(-1, "signal error");
	return (0);
}
