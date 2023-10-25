/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   exit.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: trstn4 <trstn4@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/08/25 10:37:37 by trstn4        #+#    #+#                 */
/*   Updated: 2023/10/25 12:01:05 by trstn4        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	restore_terminal_to_default(data_t data)
{
	if (tcsetattr(0, TCSANOW, &data.orig_termios) != 0)
	{
		perror("Error: Failed tcsetattr restoring terminal.");
		return (-1);
	}
	return (0);
}

void	ms_exit_shell(data_t data)
{
	printf("exit\n");
	if (restore_terminal_to_default(data) == -1)
		exit(EXIT_FAILURE);
	exit(EXIT_SUCCESS);
}
 