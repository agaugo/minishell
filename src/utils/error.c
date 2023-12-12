/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   error.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: trstn4 <trstn4@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/08/21 19:24:57 by trstn4        #+#    #+#                 */
/*   Updated: 2023/12/12 20:59:43 by trstn4        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ms_handle_error(int _exitCode, char *_errorMessage)
{
	perror(_errorMessage);
	exit(_exitCode);
}

void ms_free_2d_array(char **array)
{
    if (array == NULL)
    {
        return;
    }

    for (int i = 0; array[i] != NULL; i++)
    {
        free(array[i]);
    }

    free(array);
}

void debug(char *output)
{
	printf("Content: %s\n", output);
}