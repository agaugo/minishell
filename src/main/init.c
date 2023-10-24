/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   init.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: trstn4 <trstn4@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/24 23:38:22 by trstn4        #+#    #+#                 */
/*   Updated: 2023/10/25 00:20:09 by trstn4        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int ms_set_terminal_settings(struct termios *_oldTermios)
{
	struct termios _newTermios;
	
	if (tcgetattr(0, _oldTermios) != 0)
        handleError(-1, "tcgetattr");
	_newTermios = * _oldTermios;
	_newTermios.c_lflag &= ~ECHOCTL;
	if (tcsetattr(0, TCSANOW, &_newTermios) != 0)
        handleError(-1, "tcsetattr");
	return (0);
}

char **ms_clone_envp(char **envp)
{
    int count = 0;
    while (envp[count]) count++;

    char **new_envp = malloc(sizeof(char *) * (count + 1));
    if (!new_envp) {
        perror("Failed to allocate memory for new_envp");
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < count; i++) {
        new_envp[i] = strdup(envp[i]);
        if (!new_envp[i]) {
            perror("Failed to duplicate string for new_envp");
            exit(EXIT_FAILURE);
        }
    }
    new_envp[count] = NULL;

    return new_envp;
}
