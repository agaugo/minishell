/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   minishell.h                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: tvan-bee <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/10 17:16:15 by tvan-bee      #+#    #+#                 */
/*   Updated: 2023/08/25 12:13:24 by trstn4        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/libft.h"
#include "../includes/colors.h"

#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <termios.h>

typedef struct s_terminal
{
	int	x;
}				t_terminal;

int main();
void cd_cmd(char *path);
void exit_cmd(struct termios *old_termios);
char *get_colored_prompt();

#endif
