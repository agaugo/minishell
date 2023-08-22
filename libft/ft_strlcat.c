/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strlcat.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: tvan-bee <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/13 11:43:00 by tvan-bee      #+#    #+#                 */
/*   Updated: 2022/10/13 11:43:18 by tvan-bee      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

/*
DESCRIPTION
    strlcat() function copy and concatenate strings with the same input
	parameters and output result as snprintf(3). They are designed to be safer,
	more consistent, and less error prone replacements for the easily misused
	functions strncpy(3) and strncat(3).

    strlcat() take the full size of the destination buffer and guarantee
	NUL-termination if there is room. Note that room for the NUL should be
	included in dstsize.

    strlcat() appends string src to the end of dst.  It will append at most
	dstsize - strlen(dst) - 1 characters. It will then NUL-terminate, unless
	dstsize is 0 or the original dst string was longer than dstsize
	(in practice this should not happen as it means that either dstsize is
	incorrect or that dst is not a proper string).

    If the src and dst strings overlap, the behavior is undefined.

PARAMETERS
	dst: The destination where the source will be copied to at the end.
	src: The source to copy to the end of the destination.
	dstsize: The maximum length that will be read and copied to if there is
				room at the end.

RETURN VALUES
	strlcat() function return the total length of the string they tried to create.
	For strlcat() that means the initial length of dst plus the length of src.

    If the return value is >= dstsize, the output string has been truncated.
	It is the caller's responsibility to handle this.
*/

/*
size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	dst_len;
	size_t	src_len;
	size_t	i;
	size_t	j;

	// Length of the strings.
	dst_len = ft_strlen(dst);
	src_len = ft_strlen(src);
	i = dst_len;
	j = 0;
	// Returns the integer length of 'src' if the size is equal to '0'.
	if (dstsize == 0)
		return (src_len);
	// Returns the integer length of 'src' + 'dst' if the size is smaller then
	// 'dst_length' length.
	if (dstsize < dst_len)
		return (src_len + dstsize);
	else
	{
		// Appends each character from 'src' to 'dst' if the total length of 
		// the current size of 'dst' is not bigger than 'dstsize'.
		while (src[j] && (dst_len + j) < dstsize)
			dst[i++] = src[j++];
		// Overwrites the last added char with NULL terminator if there is no enough
		// room for 'src' added to 'dst'.
		if ((dst_len + j) == dstsize && dst_len < dstsize)
			dst[--i] = '\0';
		else
			// Adds the terminator at the end of the string if there is enough room.
			dst[i] = '\0';
		// Returns length of both parameters.
		return (src_len + dst_len);
	}
}
*/

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	dst_len;
	size_t	src_len;
	size_t	i;
	size_t	j;

	dst_len = ft_strlen(dst);
	src_len = ft_strlen(src);
	i = dst_len;
	j = 0;
	if (dstsize == 0)
		return (src_len);
	if (dstsize < dst_len)
		return (src_len + dstsize);
	else
	{
		while (src[j] && (dst_len + j) < dstsize)
			dst[i++] = src[j++];
		if ((dst_len + j) == dstsize && dst_len < dstsize)
			dst[--i] = '\0';
		else
			dst[i] = '\0';
		return (src_len + dst_len);
	}
}
