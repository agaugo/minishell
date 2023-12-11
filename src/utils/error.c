/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   error.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: trstn4 <trstn4@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/08/21 19:24:57 by trstn4        #+#    #+#                 */
/*   Updated: 2023/12/06 15:29:02 by trstn4        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ms_handle_error(int _exitCode, char *_errorMessage)
{
	perror(_errorMessage);
	exit(_exitCode);
}

void	ms_free_2d_array(char **_array)
{
	int	_index;

	_index = 0;
	while (_array[_index] != NULL)
	{
		free_memory(_array[_index]);
		_index++;
	}
	free_memory(_array);
}
void debug(char *output)
{
	printf("Content: %s\n", output);
}