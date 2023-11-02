/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cd.c                                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: trstn4 <trstn4@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/08/25 10:37:37 by trstn4        #+#    #+#                 */
/*   Updated: 2023/11/02 21:11:13 by trstn4        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	ms_cd_home(data_t *data)
{
	char	*home_path;
	char	*full;
	int		index;

	index = ms_find_env_index(data->envp, "HOME");
	if (index == -1)
	{
		perror("Environment Variable Not Found");
		return ;
	}
	full = ft_strdup(data->envp[index]);
	home_path = ft_memmove(full, full + 5, ft_strlen(full) - 4);
	if (home_path)
		chdir(home_path);
	free(full);
}

static void	ms_cd_absolute_path(data_t *data, char *path)
{
	if (!path || chdir(path) != 0)
	{
		data->last_exit_code = 1;
		ms_handle_error(1, "No such file or directory");
	}
}

void	ms_cd_command(data_t *data)
{
	char	*direction;

	if (!data->tokens->value)
		ms_cd_home(data);
	else
	{
		direction = data->tokens->next->value;
		if (access(direction, F_OK) == 0)
			ms_cd_absolute_path(data, direction);
		else
			ms_cd_absolute_path(data, NULL);
	}
	data->last_exit_code = 0;
}
