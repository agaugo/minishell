/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   path.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: trstn4 <trstn4@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/22 23:51:43 by trstn4        #+#    #+#                 */
/*   Updated: 2023/12/13 14:01:49 by trstn4        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

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
		free_memory(current_directory);
		if (errno == ERANGE)
		{
			buffer_size *= 2;
			attempts++;
		}
	}
	ms_handle_error(1, "Max attempts used for getcwd");
	return (NULL);
}

char	*read_file_content(const char *filename)
{
	char	*buffer;
	FILE	*file;
	long	length;

	file = fopen(filename, "r");
	if (!file)
	{
		perror("Unable to open file");
		return (NULL);
	}
	fseek(file, 0, SEEK_END);
	length = ftell(file);
	fseek(file, 0, SEEK_SET);
	buffer = (char *)allocate_memory(length + 1);
	if (!buffer)
	{
		fclose(file);
		ms_handle_error(-1, "Failed to read file.");
	}
	fread(buffer, 1, length, file);
	buffer[length] = '\0';
	fclose(file);
	return (buffer);
}
