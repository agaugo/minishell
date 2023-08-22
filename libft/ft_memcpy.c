/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_memcpy.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: tvan-bee <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/10 16:46:22 by tvan-bee      #+#    #+#                 */
/*   Updated: 2022/10/10 16:47:32 by tvan-bee      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

/*
DESCRIPTION
    The memcpy() function copies n bytes from memory area src to memory area
    dst. If dst and src overlap, behavior is undefined. Applications in
    which dst and src might overlap should use memmove(3) instead.

PARAMETERS
	dst: The destination where the source will be copied to.
	src: The source to copy to destination.
	n: The maximum length that will be copied.

RETURN VALUES
    The memcpy() function returns the original value of dst.
*/

/*
void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	size_t	i;

	// Returns null if first two parameters has no value.
	if (!dst && !src)
		return (NULL);
	i = 0;
	// Loop until max size reached.
	while (i < n)
	{
		// Adds each character in 'src' to the 'dst' value.
		((unsigned char *)dst)[i] = ((unsigned char *)src)[i];
		i++;
	}
	// Returns updated 'dst'.
	return (dst);
}
*/

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	size_t	i;

	if (!dst && !src)
		return (NULL);
	i = 0;
	while (i < n)
	{
		((unsigned char *)dst)[i] = ((unsigned char *)src)[i];
		i++;
	}
	return (dst);
}
