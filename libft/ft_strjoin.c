/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strjoin.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: tvan-bee <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/13 16:44:43 by tvan-bee      #+#    #+#                 */
/*   Updated: 2023/12/13 00:35:10 by trstn4        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

/*
DESCRIPTION
	Allocates (with malloc(3)) and returns a new string, which is the result
	of the concatenation of ’s1’ and ’s2’.

PARAMETERS
	s1: The prefix string.
	s2: The suffix string.

RETURN VALUES
	The new string.NULL if the allocation fails.
*/

/*
char	*ft_strjoin(char const *s1, char const *s2)
{
	char			*buffer;
	unsigned int	i;
	unsigned int	j;

	// Returns NULL if one of the two parameters has no value.
	if (!s1 || !s2)
		return (NULL);
	// Mallocs the needed size.
	buffer = (char *)malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	// Protecting malloc.
	if (!buffer)
		return (NULL);
	i = 0;
	j = 0;
	// Loop until max size reached.
	while (s1[i])
	{
		// Adding first string to the buffer.
		buffer[i] = s1[i];
		i++;
	}
	// Loop until max size reached.
	while (s2[j])
	{
		// Adding second string to the buffer.
		buffer[i] = s2[j];
		i++;
		j++;
	}
	// Adding NULL terminator at the end of the string.
	buffer[i] = '\0';
	// Returns new string.
	return (buffer);
}
*/

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char			*buffer;
	unsigned int	i;
	unsigned int	j;

	if (!s1 || !s2)
		return (NULL);
	buffer = (char *)allocate_memory(sizeof(char) * (ft_strlen(s1)
				+ ft_strlen(s2) + 1));
	if (!buffer)
		return (NULL);
	i = 0;
	j = 0;
	while (s1[i])
	{
		buffer[i] = s1[i];
		i++;
	}
	while (s2[j])
	{
		buffer[i] = s2[j];
		i++;
		j++;
	}
	buffer[i] = '\0';
	return (buffer);
}
