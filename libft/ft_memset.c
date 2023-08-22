/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_memset.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: tvan-bee <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/10 16:43:52 by tvan-bee      #+#    #+#                 */
/*   Updated: 2022/10/10 16:44:53 by tvan-bee      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

/*
DESCRIPTION
    The memset() function writes len bytes of value c
	(converted to an unsigned char) to the string b.

PARAMETERS
	b: The type which indexes will be replaced.
	c: The type that will replace the indexes.
	len: The maximum length that will be replaced.

RETURN VALUES
    The memset() function returns its first argument.
*/

/*
void	*ft_memset(void *b, int c, size_t len)
{
	unsigned char	*p;

	// Converting to unsigned char.
	p = b;
	// Loops until length has been reached.
	while (len > 0)
	{
		// Current pointer value is equal to the given character in the 'c'
		// parameter.
		*p = c;
		p++;
		len--;
	}
	// Returns destination value.
	return (b);
}
*/

#include "libft.h"

void	*ft_memset(void *b, int c, size_t len)
{
	unsigned char	*p;

	p = b;
	while (len > 0)
	{
		*p = c;
		p++;
		len--;
	}
	return (b);
}
