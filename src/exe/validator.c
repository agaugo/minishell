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

int	ms_check_absolute_path(token_t *_token)
{
	if (access(_token->value, X_OK) != -1)
		return (1);
	else
		return (0);
}

void	ms_free_2d_array(char **_array)
{
	int	_index;

	_index = 0;
	while (_array[_index] != NULL)
	{
		free(_array[_index]);
		_index++;
	}
	free(_array);
}

int	ms_validate_token(token_t *_token)
{
	int		_index;
	char	*_path;
	char	**_pathDirectories;
	char	*_fullDirectory;

	if (ms_check_absolute_path(_token))
		return (1);
	_path = getenv("PATH");
	if (_path == NULL)
	{
		ms_handle_error(2, "PATH Variable not set");
		return (0);
	}
	_pathDirectories = ft_split(_path, ':');
	_index = 0;
	while (_pathDirectories[_index] != NULL)
	{
		_fullDirectory = ft_strjoin(_pathDirectories[_index], "/");
		_fullDirectory = ft_strjoin(_fullDirectory, _token->value);
		if (access(_fullDirectory, X_OK) != -1)
		{
			_token->executableDir = _fullDirectory;
				// THIS NEEDS TO BE FREED SOMEWHERE
			ms_free_2d_array(_pathDirectories);
			return (1);
		}
		free(_fullDirectory);
		_index++;
	}
	// ERROR HANDLING HERE OR IN FUNCTION CALL SYSTEM?
	ms_free_2d_array(_pathDirectories);
	return (0);
}
