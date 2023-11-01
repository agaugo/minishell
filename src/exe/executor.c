/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   executor.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: trstn4 <trstn4@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/08/21 19:24:57 by trstn4        #+#    #+#                 */
/*   Updated: 2023/11/01 15:20:37 by trstn4        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char **ms_single_command_array(const char *_command)
{
    char **_execall;

    _execall = malloc(2 * sizeof(char *));
    if (!_execall) {
        perror("Failed to allocate memory for command array");
        return NULL;
    }
    _execall[0] = ft_strdup(_command);
    if (!_execall[0]) {
        perror("Failed to duplicate command string");
        free(_execall);
    }
    _execall[1] = NULL;

    return _execall;
}

void	ms_execute_command(data_t *data, char **_array)
{
	pid_t	pid;
    int     status;

	pid = fork();
	if (pid == -1)
	{
		ms_free_2d_array(_array);
		ms_handle_error(EXIT_FAILURE, "Fork Failure");
	}
	else if (pid == 0)
	{
        execve(_array[0], _array, data->envp);
		ms_free_2d_array(_array);
		ms_handle_error(EXIT_FAILURE, "Execve Failure");
	}
	else
	{
		wait(&status);
        int exit_status = status >> 8;
		data->last_exit_code = exit_status;
        printf("Command exited with status: %d\n", data->last_exit_code);
	}
	ms_free_2d_array(_array);
}

int	ms_count_array_len(data_t *data)
{
	int		_count;
	token_t	*_newtoken;

	_count = 0;
	_newtoken = data->tokens;
	while (_newtoken && _newtoken->type == T_WORD)
	{
		_newtoken = _newtoken->next;
		_count++;
	}
	return (_count);
}

char	**ms_get_full_args(data_t *data, char *_fullpath)
{
	char	**_returnarray;
	int		_index;
	int		_len;
	token_t *_token;

	_len = ms_count_array_len(data);
	_index = 0;
	_returnarray = (char **)malloc((_len + 1) * sizeof(char *));
	_token = data->tokens->next;
	_returnarray[_index] = ft_strdup(_fullpath);
	_index++;
	while (_token != NULL)
	{
        if (_token->type != T_WORD)
            break ;
		_returnarray[_index] = ft_strdup(_token->value);
		_token = _token->next;
		_index++;
	}
    _returnarray[_index] = NULL;
	return (_returnarray);
}

int	ms_custom_exec(data_t *data, char *_cmd)
{
	char	**_execall;

	if (ft_strchr(_cmd, '/'))
	{
		if (access(_cmd, X_OK) != -1)
		{
            if (data->tokens->next && data->tokens->next->type == T_WORD)
                _execall = ms_get_full_args(data, _cmd);
            else
                _execall = ms_single_command_array(_cmd);
			ms_execute_command(data, _execall);
		}
		else
			perror("File is a directory");
		return (1);
	}
	return (-1);
}


void	ms_identify_command(data_t *data)
{
	char	*_cmd;
	char	*_fullpath;
	char	**_allpath;
	char	**_execall;
	int		_index;

	_cmd = data->tokens->value;
	if (ms_custom_exec(data, _cmd) == 1)
		return ;
	_allpath = ft_split(getenv("PATH"), ':');
	_index = 0;
	while (_allpath[_index] != NULL)
	{
		_allpath[_index] = ft_strjoin(_allpath[_index], "/");
		_fullpath = ft_strjoin(_allpath[_index], _cmd);
		if (access(_fullpath, X_OK) != -1)
		{
            if (data->tokens->next && data->tokens->next->type == T_WORD)
                _execall = ms_get_full_args(data, _fullpath);
            else
                _execall = ms_single_command_array(_fullpath);
			ms_execute_command(data, _execall);
			return ;
		}
		_index++;
	}
	perror("Invalid Command");
}
