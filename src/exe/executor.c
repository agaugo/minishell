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

#include "../../includes/minishell.h"

void	ms_execute_command(char **_array, char **_envp)
{
	pid_t	pid;

	pid = fork();  // Create a child process
	if (pid == -1) // Fork failed
	{
		ms_free_2d_array(_array);
		ms_handle_error(EXIT_FAILURE, "Fork Failure");
	}
	else if (pid == 0) // In child process
	{
		execve(_array[0], _array, _envp);
		ms_free_2d_array(_array);
		ms_handle_error(EXIT_FAILURE, "Execve Failure");
			// will only run if execve fails
	}
	else
	{
		wait(NULL); // Wait for child process to finish
	}
	ms_free_2d_array(_array);
}

int	ms_count_array_len(token_t *_token)
{
	int		_count;
	token_t	*_newtoken;

	_count = 0;
	_newtoken = _token;
	while (_newtoken)
	{
		_newtoken = _newtoken->next;
		_count++;
	}
	return (_count);
}

char	**ms_get_full_args(token_t *_token, char *_fullpath)
{
	char	**_returnarray;
	int		_index;
	int		_len;

	_len = ms_count_array_len(_token);
	_index = 0;
	_returnarray = (char **)malloc((_len + 1) * sizeof(char *));
	_returnarray[_len] = NULL;
	_token = _token->next;
	_returnarray[_index] = ft_strdup(_fullpath);
	_index++;
	while (_token != NULL)
	{
		_returnarray[_index] = ft_strdup(_token->value);
		_token = _token->next;
		_index++;
	}
	return (_returnarray);
}

int	ms_custom_exec(token_t *_token, char *_cmd)
{
	char	**_execall;

	if (ft_strchr(_cmd, '/'))
	{
		if (access(_cmd, X_OK) != -1)
		{
			_execall = ms_get_full_args(_token, _cmd);
			ms_execute_command(_execall, _token->envp);
		}
		else
			perror("No such file or Directory");
		return (1);
	}
	return (-1);
}

void	ms_identify_command(token_t *_token)
{
	char	*_cmd;
	char	*_fullpath;
	char	**_allpath;
	char	**_execall;
	int		_index;

	_cmd = _token->value;
	if (ms_custom_exec(_token, _cmd) == 1)
		return ;
	_allpath = ft_split(getenv("PATH"), ':');
	_index = 0;
	while (_allpath[_index] != NULL)
	{
		_allpath[_index] = ft_strjoin(_allpath[_index], "/");
		_fullpath = ft_strjoin(_allpath[_index], _cmd);
		if (access(_fullpath, X_OK) != -1)
		{
			_execall = ms_get_full_args(_token, _fullpath);
			ms_execute_command(_execall, _token->envp);
			return ;
		}
		_index++;
	}
	perror("Invalid Command");
}
