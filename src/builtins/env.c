/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   env.c                                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: trstn4 <trstn4@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/23 00:04:00 by trstn4        #+#    #+#                 */
/*   Updated: 2023/12/13 14:28:03 by trstn4        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ms_print_env_variables(t_data *data)
{
	int		index;

	index = 0;
	while (data->envp[index] != NULL)
	{
		printf("%s\n", data->envp[index]);
		index++;
	}
	data->last_exit_code = 0;
}
