/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   exe_resolve_paths.c                                :+:    :+:            */
/*                                                     +:+                    */
/*   By: trstn4 <trstn4@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/08/21 19:24:57 by trstn4        #+#    #+#                 */
/*   Updated: 2023/12/13 10:54:31 by trstn4        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ms_set_command_path(char **allpath, token_t *current)
{
	char	*fullpath;
	char	*temp;
	int		i;
	int		found;

	i = 0;
	found = 0;
	while (allpath[i])
	{
		temp = ft_strjoin(allpath[i], "/");
		fullpath = ft_strjoin(temp, current->value);
		free_memory(temp);
		if (access(fullpath, X_OK) != -1)
		{
			found = 1;
			free_memory(current->value);
			current->value = fullpath;
			break ;
		}
		free_memory(fullpath);
		i++;
	}
	return (found);
}

int	ms_is_directory(const char *path)
{
	struct stat	statbuf;

	if (stat(path, &statbuf) != 0)
		return (0);
	return (S_ISDIR(statbuf.st_mode));
}

void	ms_set_resolve_error(data_t *data, token_t *current, char **allpath)
{
	if (ft_strchr(current->value, '/') != NULL)
	{
		if (ms_is_directory(current->value))
		{
			data->last_exit_code = 126;
			current->status = 126;
		}
	}
	else
	{
		if (!ms_set_command_path(allpath, current))
		{
			data->last_exit_code = 127;
			current->status = 127;
		}
	}
}

void	ms_resolve_loop(data_t *data, token_t *current, char **allpath)
{
	int	is_command;

	is_command = 1;
	while (current)
	{
		if (current->type == T_WORD && is_command
			&& !ms_is_builtin_command(current->value))
		{
			ms_set_resolve_error(data, current, allpath);
		}
		if (current->type == T_PIPE)
			is_command = 1;
		else
			is_command = 0;
		current = current->next;
	}
}

void	ms_resolve_command_paths(data_t *data)
{
	char	**allpath;
	char	*path;

	path = ft_getenv(data->envp, "PATH");
	if (!path)
		return ;
	allpath = ft_split(path, ':');
	ms_resolve_loop(data, data->tokens, allpath);
	ms_free_2d_array(allpath);
	free_memory(path);
}
