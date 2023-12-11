/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strdup.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: tvan-bee <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/13 13:46:59 by tvan-bee      #+#    #+#                 */
/*   Updated: 2022/10/13 13:47:01 by tvan-bee      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "libft.h"
#include "../includes/minishell.h"


int count = 0;

char	*ft_strdup(const char *s1)
{
	char		*buffer;
	size_t		s1_len;

	s1_len = ft_strlen(s1) + 1;
	buffer = (char *)allocate_memory(sizeof(char) * s1_len);
	if (!buffer)
		return (NULL);
	count++;
	ft_memcpy(buffer, s1, s1_len);
	return (buffer);
}