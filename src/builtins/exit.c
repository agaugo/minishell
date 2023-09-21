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

//RESTORE TERMINAL TO DEFAULT
int ms_restoreTerminal(struct termios *_oldTermios) {
    if (tcsetattr(0, TCSANOW, _oldTermios)!= 0)
        ms_handleError(-1, "tcsetattr: Error restoring terminal");
    return (0);
}

// EXIT SHELL
void ms_exitShell(struct termios *_oldTermios) {
    printf("//exit//\n");
    ms_restoreTerminal(_oldTermios);
    exit(0);
}