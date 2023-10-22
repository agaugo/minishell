/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   env.c                                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: trstn4 <trstn4@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/23 00:04:00 by trstn4        #+#    #+#                 */
/*   Updated: 2023/10/23 00:21:47 by trstn4        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ms_print_env_variables(token_t *token)
{
	char	**env_vars;
	int		index;

	index = 0;
	env_vars = token->envp;
	while (env_vars[index] != NULL)
	{
		printf("%s\n", env_vars[index]);
		index++;
	}
}
