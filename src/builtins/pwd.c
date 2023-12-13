/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   pwd.c                                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: trstn4 <trstn4@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/22 23:51:43 by trstn4        #+#    #+#                 */
/*   Updated: 2023/12/13 14:28:11 by trstn4        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ms_pwd_command(t_data *data)
{
	char	*current_directory;

	current_directory = ms_get_current_working_dir();
	printf("%s\n", current_directory);
	free_memory(current_directory);
	data->last_exit_code = 0;
}
