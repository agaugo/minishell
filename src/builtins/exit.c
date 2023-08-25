/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   exit.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: trstn4 <trstn4@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/08/25 10:37:37 by trstn4        #+#    #+#                 */
/*   Updated: 2023/08/25 12:24:07 by trstn4        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void exit_cmd(struct termios *old_termios)
{
    printf("exit\n");
	tcsetattr(0, TCSANOW, old_termios);
	exit(0);
}
