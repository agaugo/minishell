/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   error.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: trstn4 <trstn4@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/08/21 19:24:57 by trstn4        #+#    #+#                 */
/*   Updated: 2023/12/13 17:53:36 by trstn4        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ms_handle_error(int exit_code, char *message)
{
	perror(message);
	exit(exit_code);
}

void	ms_free_2d_array(char **array)
{
	int	i;

	i = 0;
	if (array == NULL)
		return ;
	while (array[i] != NULL)
	{
		free_memory(array[i]);
		i++;
	}
	free_memory(array);
}

#include <stdlib.h>
#include <string.h>

char *ft_strjoin_free(char *s1, char *s2)
{
    char *new_str;
    size_t len1 = s1 ? ft_strlen(s1) : 0;
    size_t len2 = s2 ? ft_strlen(s2) : 0;
    size_t i, j;

    new_str = allocate_memory(len1 + len2 + 1);
    if (!new_str) {
        return NULL;
    }

    for (i = 0; i < len1; i++) {
        new_str[i] = s1[i];
    }

    for (j = 0; j < len2; j++) {
        new_str[i + j] = s2[j];
    }

    new_str[i + j] = '\0';

    free_memory(s1);
    free_memory(s2);
    
    return new_str;
}
