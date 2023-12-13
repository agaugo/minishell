/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   term.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: tvan-bee <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/10 17:16:15 by tvan-bee      #+#    #+#                 */
/*   Updated: 2023/12/13 14:17:31 by trstn4        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

struct termios	enable_noncanonical_mode(void)
{
	struct termios	new_termios;
	struct termios	old_termios;

	if (tcgetattr(STDIN_FILENO, &old_termios) == -1)
		return (old_termios);
	new_termios = old_termios;
	new_termios.c_lflag &= ~ECHOCTL;
	if (tcsetattr(STDIN_FILENO, TCSANOW, &new_termios) == -1)
		return (old_termios);
	return (old_termios);
}
