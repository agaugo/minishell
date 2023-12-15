/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   path.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: trstn4 <trstn4@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/22 23:51:43 by trstn4        #+#    #+#                 */
/*   Updated: 2023/12/14 12:30:27 by trstn4        ########   odam.nl         */
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

static char	*ms_read_realloc(char *buffer, int *fd, size_t *buffer_size,
		size_t *total_read)
{
	char	*new_buffer;

	if (*total_read == *buffer_size)
	{
		*buffer_size *= 2;
		new_buffer = memory_realloc(buffer, *buffer_size);
		if (!new_buffer)
		{
			free_memory(buffer);
			close(*fd);
			return (NULL);
		}
		buffer = new_buffer;
	}
	return (buffer);
}

static char	*ms_file_read_loop(char *buffer, int *fd, size_t *buffer_size,
		size_t *total_read)
{
	size_t	bytes_read;

	while (1)
	{
		ms_read_realloc(buffer, fd, buffer_size, total_read);
		bytes_read = read(*fd, buffer + *total_read,
				*buffer_size - *total_read - 1);
		if (bytes_read == 0)
			break ;
		total_read += bytes_read;
	}
	if (bytes_read == 0)
		return (buffer);
	else
	{
		free_memory(buffer);
		close(*fd);
		perror("Error reading file");
		return (NULL);
	}
}

char	*read_file_content(const char *filename)
{
	int		fd;
	char	*buffer;
	size_t	buffer_size;
	size_t	total_read;

	buffer_size = 1024;
	total_read = 0;
	fd = open(filename, O_RDONLY);
	if (fd == -1)
	{
		perror("Unable to open file");
		return (NULL);
	}
	buffer = allocate_memory(buffer_size);
	if (!buffer)
	{
		close(fd);
		return (NULL);
	}
	buffer = ms_file_read_loop(buffer, &fd, &buffer_size, &total_read);
	if (buffer)
		buffer[total_read] = '\0';
	close(fd);
	return (buffer);
}
