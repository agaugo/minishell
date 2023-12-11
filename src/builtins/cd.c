/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cd.c                                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: trstn4 <trstn4@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/08/25 10:37:37 by trstn4        #+#    #+#                 */
/*   Updated: 2023/12/09 16:54:24 by trstn4        ########   odam.nl         */
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
	free_memory(home_path);
}

static void	ms_cd_absolute_path(data_t *data, char *path)
{
	data->last_path = ms_get_current_working_dir();
	if (!path || chdir(path) != 0)
	{
		data->last_exit_code = 1;
		// ms_handle_error(1, "No such file or directory");
		perror("cd");
	}
}

void	ms_cd_command(data_t *data, token_t *token)
{
	char	*direction;

	data->last_exit_code = 0;
	if (!token->next)
		ms_cd_home(data);
	else
	{
		if (token->next->type == T_PIPE)
			return ;
		
		direction = token->next->value;

		if (ft_strcmp(direction, "-") == 0)
		{
			ms_cd_absolute_path(data, data->last_path);
			printf("%s\n", data->last_path);
		}
		else
		{
			if (access(direction, F_OK) == 0)
				ms_cd_absolute_path(data, direction);
			else
				ms_cd_absolute_path(data, NULL);
		}
	}
}
