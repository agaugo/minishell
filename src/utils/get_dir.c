/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_dir.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: trstn4 <trstn4@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/11/02 20:39:35 by trstn4        #+#    #+#                 */
/*   Updated: 2023/11/02 20:39:37 by trstn4        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static char	*alloc_mem(size_t buffer_size)
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
		current_directory = alloc_mem(buffer_size);
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
	ms_handle_error(1, "Max attempts used for getcwd");
	return (NULL);
}
