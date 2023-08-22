/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_memcmp.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: tvan-bee <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/11 15:20:05 by tvan-bee      #+#    #+#                 */
/*   Updated: 2022/10/11 15:20:28 by tvan-bee      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

/*
DESCRIPTION
    The memcmp() function compares byte string s1 against byte string s2.
	Both strings are assumed to be n bytes long.

PARAMETERS
	s1: The type that will be compared with type2.
	s2: The type that will be compared with type1.
	n: The maximum length in the types that will be checked.

RETURN VALUES
    The memcmp() function returns zero if the two strings are identical,
	otherwise returns the difference between the first two differing bytes
	(treated as unsigned char values, so that `\200' is greater than `\0',
	for example). Zero-length strings are always identical. This behavior is
	not required by C and portable code should only depend on the sign of the
	returned value.
*/

/*
int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	size_t				i;
	const unsigned char	*ss1;
	const unsigned char	*ss2;

	i = 0;
	// Typecasting to unsigned.
	ss1 = (const unsigned char *)s1;
	ss2 = (const unsigned char *)s2;
	// Loop until max size reached.
	while (i < n)
	{
		// Returns the difference between the two chars.
		if (ss1[i] != ss2[i])
			return (ss1[i] - ss2[i]);
		i++;
	}
	// Returns zero if identical.
	return (0);
}
*/

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	size_t				i;
	const unsigned char	*ss1;
	const unsigned char	*ss2;

	i = 0;
	ss1 = (const unsigned char *)s1;
	ss2 = (const unsigned char *)s2;
	while (i < n)
	{
		if (ss1[i] != ss2[i])
			return (ss1[i] - ss2[i]);
		i++;
	}
	return (0);
}
