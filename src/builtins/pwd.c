/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   pwd.c                                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: trstn4 <trstn4@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/22 23:51:43 by trstn4        #+#    #+#                 */
/*   Updated: 2023/11/27 19:41:21 by trstn4        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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

void	ms_pwd_command(data_t *data)
{
	char *current_directory;

	current_directory = ms_get_current_working_dir();
	printf("%s\n", current_directory);
	free_memory(current_directory);
	data->last_exit_code = 0;
}
