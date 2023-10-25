/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cd.c                                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: trstn4 <trstn4@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/08/25 10:37:37 by trstn4        #+#    #+#                 */
/*   Updated: 2023/10/25 11:51:03 by trstn4        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	cd_home(data_t data)
{
	char	*home_path;
	char	*full;
	int		index;

	index = find_env_index(data.envp, "HOME");
	if (index == -1)
	{
		perror("Environment Variable Not Found");
		return ;
	}
	full = ft_strdup(data.envp[index]);
	home_path = ft_memmove(full, full + 5, ft_strlen(full) - 4);
	if (home_path)
		chdir(home_path);
}

static void	cd_absolute_path(char *path)
{
	if (!path || chdir(path) != 0)
		perror("Error: No such file or directory.");
}

void	ms_cd_command(data_t data)
{
	char	*direction;

	if (data.tokens->next == NULL)
		cd_home(data);
	else
	{
		direction = data.tokens->next->value;
		if (access(direction, F_OK) == 0)
			cd_absolute_path(direction);
		else
			cd_absolute_path(NULL);
	}
}
