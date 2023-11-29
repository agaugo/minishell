/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cd.c                                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: trstn4 <trstn4@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/08/25 10:37:37 by trstn4        #+#    #+#                 */
/*   Updated: 2023/11/28 17:08:12 by trstn4        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	ms_cd_home(data_t *data)
{
	char	*home_path;

    home_path = ft_getenv(data->envp, "HOME");
	if (home_path == NULL)
	{
		perror("Environment Variable Not Found");
		return ;
	}
    chdir(home_path);
	free(home_path);
}

static void	ms_cd_absolute_path(data_t *data, char *path)
{
	if (!path || chdir(path) != 0)
	{
		data->last_exit_code = 1;
		ms_handle_error(1, "No such file or directory");
	}
}

void	ms_cd_command(data_t *data, token_t *token)
{
	char	*direction;

	if (!token->next)
		ms_cd_home(data);
	else
	{
		direction = token->next->value;
		if (access(direction, F_OK) == 0)
			ms_cd_absolute_path(data, direction);
		else
			ms_cd_absolute_path(data, NULL);
	}
	data->last_exit_code = 0;
}
