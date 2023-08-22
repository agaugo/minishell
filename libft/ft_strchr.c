/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strchr.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: tvan-bee <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/10 16:42:34 by tvan-bee      #+#    #+#                 */
/*   Updated: 2022/10/10 16:43:34 by tvan-bee      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

/*
DESCRIPTION
    The strchr() function locates the first occurrence of c (converted to a
    char) in the string pointed to by s. The terminating null character is
    considered to be part of the string; therefore if c is `\0', the func-
    tions locate the terminating `\0'.

PARAMETERS
	s: The string that will be checked.
	c: The char that needs to be found.

RETURN VALUES
    The function strchr() return a pointer to the located character, or NULL
	if the character does not appear in the string.
*/

/*
char	*ft_strchr(const char *s, int c)
{
	// Loops until the first occurrence of the given char is found in 's'.
	while ((char)c != *s)
	{
		// Returns null if the current pointer of 's' is equal to terminator.
		if (!*s)
			return (NULL);
		s++;
	}
	// Returns the remaining string if the first occurrence of the given char
	// is found in 's'.
	return ((char *)s);
}
*/

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	while ((char)c != *s)
	{
		if (!*s)
			return (NULL);
		s++;
	}
	return ((char *)s);
}
