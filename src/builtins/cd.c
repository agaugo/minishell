/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cd.c                                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: trstn4 <trstn4@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/08/25 10:37:37 by trstn4        #+#    #+#                 */
/*   Updated: 2023/12/14 00:34:43 by trstn4        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	ms_cd_home(t_data *data)
{
	char	*home_path;

	home_path = ft_getenv(data->envp, "HOME");
	if (!home_path)
	{
		data->last_exit_code = 1;
		perror("cd");
		return ;
	}
	chdir(home_path);
	if (chdir(home_path) != 0)
	{
		data->last_exit_code = 1;
		perror("cd");
	}
	free_memory(home_path);
}

static void	ms_cd_absolute_path(t_data *data, char *path)
{
	char	*cwd;

	cwd = ms_get_current_working_dir();
	free_memory(data->last_path);
	data->last_path = cwd;
	if (!path || chdir(path) != 0)
	{
		data->last_exit_code = 1;
		perror("cd");
	}
}

int	ms_cd_check_error(t_data *data, t_token_t *token)
{
	data->last_exit_code = 0;
	if (token->next && token->next->next && token->next->next->type != T_PIPE)
	{
		ft_putendl_fd("minishell: too many arguments", STDERR);
		data->last_exit_code = 1;
		return (-1);
	}
	return (0);
}

void	ms_cd_command(t_data *data, t_token_t *token)
{
	char	*direction;

	if (ms_cd_check_error(data, token) == -1)
		return ;
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
