/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.h                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: tvan-bee <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/10 17:16:15 by tvan-bee      #+#    #+#                 */
/*   Updated: 2023/10/25 00:20:06 by trstn4        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAIN_H
# define MAIN_H

// Location: /src/main/init.c
int		ms_set_terminal_settings(struct termios *_oldTermios);
char	**ms_clone_envp(char **envp);

// Location: /src/main/signal.c
void	ms_handle_ctrl_c(int _signalNumber);
void	ms_handle_ctrl_d(struct termios *_oldTermios, char *_userInput);
void	ms_handle_ctrl_backspace(int _signalNumber);
int		ms_init_signals(void);

#endif
