/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   init.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: trstn4 <trstn4@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/24 23:38:22 by trstn4        #+#    #+#                 */
/*   Updated: 2023/10/25 15:09:17 by trstn4        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	**ms_clone_envp(char **envp)
{
	int		count;
	char	**new_envp;

	count = 0;
	while (envp[count])
		count++;
	new_envp = malloc(sizeof(char *) * (count + 1));
	if (!new_envp)
		ms_handle_error(EXIT_FAILURE, "Failed to allocate memory for new_envp");
	for (int i = 0; i < count; i++)
	{
		new_envp[i] = strdup(envp[i]);
		if (!new_envp[i])
			ms_handle_error(EXIT_FAILURE,
				"Failed to duplicate string for new_envp");
	}
	new_envp[count] = NULL;
	return (new_envp);
}
