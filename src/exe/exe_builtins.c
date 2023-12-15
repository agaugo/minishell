/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   exe_builtins.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: trstn4 <trstn4@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/08/21 19:24:57 by trstn4        #+#    #+#                 */
/*   Updated: 2023/12/15 15:37:38 by trstn4        ########   odam.nl         */
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

int	ms_run_builtin(t_data *data, char **args, t_token_t *current)
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
	return (data->last_exit_code);
}

void	ms_builtin_exitcode(t_data *data, t_exec_t_data *cmd_data)
{
	int	is_last_command;

	is_last_command = 0;
	if (cmd_data->next_command == NULL)
		is_last_command = 1;
	cmd_data->builtin_exit_status = ms_run_builtin(data, cmd_data->args,
			cmd_data->current);
	cmd_data->has_builtin = 1;
	if (is_last_command == 1)
		cmd_data->last_is_builtin = 1;
}
