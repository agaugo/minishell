/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   builtins.h                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: tvan-bee <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/10 17:16:15 by tvan-bee      #+#    #+#                 */
/*   Updated: 2023/10/24 23:08:31 by trstn4        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

#include "lexer.h"

#include <termios.h>

// Location: /src/builtins/cd.c
void	ms_cd_command(token_t *_token);

// Location: /src/builtins/echo.c
void	ms_echo_command(token_t *token);

// Location: /src/builtins/env.c
void	ms_print_env_variables(token_t *token);

// Location: /src/builtins/exit.c
void	ms_exit_shell(struct termios *old_termios);

// Location: /src/builtins/export.c
void	ms_export_command(token_t *token, char ***cloned_envp_ptr);

// Location: /src/builtins/pwd.c
char	*ms_get_current_working_dir(void);

// Location: /src/builtins/unset.c
void	ms_unset_command(token_t *_token, char ***envp);

#endif
