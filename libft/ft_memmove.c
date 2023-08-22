/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_memmove.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: tvan-bee <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/10 16:45:32 by tvan-bee      #+#    #+#                 */
/*   Updated: 2022/10/13 11:43:35 by tvan-bee      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

/*
DESCRIPTION
    The memmove() function copies len bytes from string src to string dst.
	The two strings may overlap; the copy is always done in a non-destructive
	manner.

PARAMETERS
	dst: The destination where the source will be copied to.
	src: The source to copy to destination.
	len: The maximum length that will be copied.

RETURN VALUES
    The memmove() function returns the original value of dst.
*/

/*
void	*ft_memmove(void *dst, const void *src, size_t len)
{
	char	*s;
	char	*d;
	size_t	i;

	// Typecasting to 'char pointer'.
	d = (char *)dst;
	s = (char *)src;
	i = 0;
	// Returns 'dst' if 'd' is equal to 's'.
	if (d == s)
		return (dst);
	// Returns NULL if both parameters have no value.
	if (!dst && !src)
		return (NULL);
	// Passes if 'dst' is bigger than 'src'.
	if (d > s)
	{
		// Loop until max size reached.
		while (len-- > 0)
			// Replaces each character from 's' to 'd' reversed.
			d[len] = s[len];
	}
	else
	{
		// Loop until max size reached.
		while (i < len)
		{
			// Assigns the char in 's' to 'd'.
			d[i] = s[i];
			i++;
		}
	}
	// Returns updated 'dst'.
	return (dst);
}
*/

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	char	*s;
	char	*d;
	size_t	i;

	i = 0;
	d = (char *)dst;
	s = (char *)src;
	if (d == s)
		return (dst);
	if (d > s)
	{
		while (len-- > 0)
			d[len] = s[len];
	}
	else
	{
		while (i < len)
		{
			d[i] = s[i];
			i++;
		}
	}
	return (dst);
}
