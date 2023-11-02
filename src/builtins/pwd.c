/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   pwd.c                                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: trstn4 <trstn4@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/22 23:51:43 by trstn4        #+#    #+#                 */
/*   Updated: 2023/11/02 09:51:57 by trstn4        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static char	*allocate_memory(size_t buffer_size)
{
	char	*current_directory;

	current_directory = (char *)malloc(buffer_size);
	if (!current_directory)
		ms_handle_error(-1, "Error: Malloc failed to allocate memory.");
	return (current_directory);
}

char	*ms_get_current_working_dir(void)
{
	char	*current_directory;
	size_t	buffer_size;
	int		attempts;

	buffer_size = 1024;
	attempts = 0;
	while (attempts < 5)
	{
		current_directory = allocate_memory(buffer_size);
		if (!current_directory)
			return (NULL);
		if (getcwd(current_directory, buffer_size) != NULL)
			return (current_directory);
		free(current_directory);
		if (errno == ERANGE)
		{
			buffer_size *= 2;
			attempts++;
		}
	}
	ms_handle_error(1, "Max attempts used to call getcwd");
	return (NULL);
}
