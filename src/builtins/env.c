/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   env.c                                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: trstn4 <trstn4@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/23 00:04:00 by trstn4        #+#    #+#                 */
/*   Updated: 2023/10/25 11:41:00 by trstn4        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ms_print_env_variables(data_t data)
{
	char	**env_vars;
	int		index;

	index = 0;
	env_vars = data.envp;
	while (env_vars[index] != NULL)
	{
		printf("%s\n", env_vars[index]);
		index++;
	}
}
