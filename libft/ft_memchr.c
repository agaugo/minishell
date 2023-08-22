/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_memchr.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: tvan-bee <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/10 16:47:48 by tvan-bee      #+#    #+#                 */
/*   Updated: 2022/10/13 11:44:13 by tvan-bee      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

/*
DESCRIPTION
    The memchr() function locates the first occurrence of c (converted to an
    unsigned char) in string s.

PARAMETERS
	s: The type that will be checked.
	c: The type that needs to be found.
	n: The maximum length that will be checked.

RETURN VALUES
    The memchr() function returns a pointer to the byte located, or NULL if no
	such byte exists within n bytes.
*/

/*
void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t	i;

	i = 0;
	// Loop until max size reached.
	while (i < n)
	{
		// Returns the remaining string if the first occurrence of the given
		// char is found.
		if (((unsigned char *)s)[i] == (unsigned char)c)
			return ((void *)(s + i));
		i++;
	}
	// Returns null.
	return (NULL);
}
*/

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n)
	{
		if (((unsigned char *)s)[i] == (unsigned char)c)
			return ((void *)(s + i));
		i++;
	}
	return (NULL);
}
