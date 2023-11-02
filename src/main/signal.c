/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   signal.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: trstn4 <trstn4@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/24 23:57:59 by trstn4        #+#    #+#                 */
/*   Updated: 2023/11/02 11:25:22 by trstn4        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// "ctrl-C"
void	ms_handle_ctrl_c(int _signalNumber)
{
	(void)_signalNumber;
	printf("\n");
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

// "ctrl-D"
void ms_handle_ctrl_d(data_t *data)
{
    if (!data->user_input)
        ms_exit_shell(data, NULL);
}

// "ctrl-\"
void	ms_handle_ctrl_backspace(int _signalNumber)
{
	(void)_signalNumber;
}

int	ms_init_signals(void)
{
	if (signal(SIGINT, ms_handle_ctrl_c) == SIG_ERR || signal(SIGQUIT,
			ms_handle_ctrl_backspace) == SIG_ERR)
		ms_handle_error(-1, "sigquit");
	return (0);
}
