/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: trstn4 <trstn4@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/08/21 19:24:57 by trstn4        #+#    #+#                 */
/*   Updated: 2023/10/25 00:20:21 by trstn4        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/lexer.h"
#include "../../includes/minishell.h"
#include <fcntl.h>

int	ms_load_fd(token_t *_token, tokentype_t _direction)
{
	int	_FD;

	if (_direction == T_REDIRECT_IN)
	{
		_FD = open(_token->value, O_RDONLY, 0666);
		if (_FD == -1)
			ms_handle_error(1, "Unable to Open Input File");
	}
	if (_direction == T_REDIRECT_OUT)
	{
		_FD = open(_token->value, O_WRONLY | O_CREAT | O_TRUNC, 0666);
		if (_FD == -1)
			ms_handle_error(1, "Unable to Open Input File");
	}
	return (_FD);
}

void	ms_handle_redirect(token_t *_token, tokentype_t _direction)
{
	int _pipe[2];
	int _FD;

	if (pipe(_pipe) == -1)
		ms_handle_error(2, "Pipe Creation Error.");
	_FD = ms_load_fd(_token, _direction);
	if (_direction == T_REDIRECT_IN)
	{
		if (dup2(_FD, 0) == -1)
			ms_handle_error(2, "Error Redirecting Input to FD");
		if (dup2(_pipe[1], 1) == -1)
			ms_handle_error(2, "Error Redirecting out to Pipe");
	}
	if (_direction == T_REDIRECT_OUT)
	{
		if (dup2(_FD, 1) == -1)
			ms_handle_error(2, "Error Redirecting Output to FD");
		if (dup2(_pipe[0], 0) == -1)
			ms_handle_error(2, "Error Redirecting In to Pipe");
	}
	_token->_pipe = _pipe;
	// THIS DOES NOT WORK FOR REDIRECT IN AND OUT
}
