/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strlcpy.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: tvan-bee <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/10 16:37:17 by tvan-bee      #+#    #+#                 */
/*   Updated: 2022/10/11 12:39:07 by tvan-bee      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

/*
DESCRIPTION
    The strlcpy() function copy and concatenate strings with the same input
    parameters and output result as snprintf(3). They are designed to be
	safer, more consistent, and less error prone replacements for the easily
	misused function strncpy(3).

    strlcpy() take the full size of the destination buffer and guarantee
	NUL-termination if there is room.  Note that room for the NUL should be
	included in dstsize.

    strlcpy() copies up to dstsize - 1 characters from the string src to dst,
	NUL-terminating the result if dstsize is not 0.

    If the src and dst strings overlap, the behavior is undefined.

PARAMETERS
	dst: The destination where the source will be copied to.
	src: The source to copy to the destination.
	dstsize: The maximum length that will be copied.

RETURN VALUES
    Besides quibbles over the return type (size_t versus int) and signal
	handler safety (snprintf(3) is not entirely safe on some systems), the
	following two are equivalent:

        n = strlcpy(dst, src, len);
        n = snprintf(dst, len, "%s", src);

    Like snprintf(3), the strlcpy() and strlcat() functions return the
	total length of the string they tried to create. For strlcpy() that
	means the length of src. For strlcat() that means the initial length
	of dst plus the length of src.

    If the return value is >= dstsize, the output string has been truncated.
	It is the caller's responsibility to handle this.
*/

/*
size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t	i;

	i = 0;
	// Checks if 'dstsize' has any value.
	if (dstsize)
	{
		// Loop until max size reached or 'src' has reached null temrinator.
		while (src[i] && i < (dstsize - 1))
		{
			// Assigns each index from 'src' to 'dst'.
			dst[i] = src[i];
			i++;
		}
		// Adds the NULL terminator to the end of the string.
		dst[i] = '\0';
	}
	// Returns the length of 'src'.
	return (ft_strlen(src));
}
*/

#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t	i;

	i = 0;
	if (dstsize)
	{
		while (src[i] && i < (dstsize - 1))
		{
			dst[i] = src[i];
			i++;
		}
		dst[i] = '\0';
	}
	return (ft_strlen(src));
}
