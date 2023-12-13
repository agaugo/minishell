/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   exe_builtins.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: trstn4 <trstn4@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/08/21 19:24:57 by trstn4        #+#    #+#                 */
/*   Updated: 2023/12/13 08:59:51 by trstn4        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ms_is_builtin_command(char *command)
{
	const char	*builtins[] = {"echo", "cd", "export", "unset", "env", "exit",
		"pwd", NULL};
	int			i;

	if (command == NULL)
		return (1);
	i = 0;
	while (builtins[i] != NULL)
	{
		if (ft_strcmp(command, builtins[i]) == 0)
		{
			return (1);
		}
		i++;
	}
	return (0);
}

void	ms_run_builtin(data_t *data, char **args, token_t *current)
{
	if (ft_strcmp(args[0], "export") == 0)
		ms_export_command(data, current);
	else if (ft_strcmp(args[0], "unset") == 0)
		ms_unset_command(data, current);
	else if (ft_strcmp(args[0], "env") == 0)
		ms_print_env_variables(data);
	else if (ft_strcmp(args[0], "pwd") == 0)
		ms_pwd_command(data);
	else if (ft_strcmp(args[0], "cd") == 0)
		ms_cd_command(data, current);
	else if (ft_strcmp(args[0], "echo") == 0)
		ms_echo_command(data, current);
	else if (ft_strcmp(args[0], "exit") == 0)
		ms_exit_shell(data, current->next);
}
