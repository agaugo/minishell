/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strncmp.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: tvan-bee <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/10 16:35:56 by tvan-bee      #+#    #+#                 */
/*   Updated: 2022/10/13 11:42:39 by tvan-bee      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

/*
DESCRIPTION
    The strcmp() and strncmp() functions lexicographically compare the
	null-terminated strings s1 and s2.

    The strncmp() function compares not more than n characters. Because strncmp()
	is designed for comparing strings rather than binary data, characters that
	appear after a `\0' character are not compared.

PARAMETERS
	s1: The string that will be compared with string2.
	s2: The string that will be compared with string1.
	n: The maximum length in the strings that will be checked.

RETURN VALUES
    The strcmp() and strncmp() functions return an integer greater than, equal
	to, or less than 0, according as the string s1 is greater than, equal to,
	or less than the string s2. The comparison is done using unsigned characters,
	so that `\200' is greater than `\0'.
*/

/*
int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	// Returns zero if value is equal to zero.
	if (n == 0)
		return (0);
	// Loops until parameter values is not equal to eachother.
	while (s1[i] && s2[i] && s1[i] == s2[i] && i < n - 1)
		i++;
	// Divides the non-equal values as 'unsigned char' values.
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}
*/

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	if (n == 0)
		return (0);
	while (s1[i] && s2[i] && s1[i] == s2[i] && i < n - 1)
		i++;
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}
