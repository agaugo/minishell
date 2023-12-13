/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   term.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: tvan-bee <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/10 17:16:15 by tvan-bee      #+#    #+#                 */
/*   Updated: 2023/12/13 14:09:47 by trstn4        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

struct	termios enable_noncanonical_mode(void)
{
	struct termios newTermios;
	struct termios oldTermios;

	if (tcgetattr(STDIN_FILENO, &oldTermios) == -1)
		return (oldTermios);
	newTermios = oldTermios;
	newTermios.c_lflag &= ~ECHOCTL;
	if (tcsetattr(STDIN_FILENO, TCSANOW, &newTermios) == -1)
		return (oldTermios);
	return (oldTermios);
}
