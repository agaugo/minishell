/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   pwd.c                                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: trstn4 <trstn4@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/22 23:51:43 by trstn4        #+#    #+#                 */
/*   Updated: 2023/11/02 20:45:04 by trstn4        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ms_pwd_command(data_t *data)
{
	printf("%s\n", ms_get_current_working_dir());
	data->last_exit_code = 0;
}
