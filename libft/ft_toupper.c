/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_toupper.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: tvan-bee <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/10 16:26:40 by tvan-bee      #+#    #+#                 */
/*   Updated: 2022/10/10 16:27:50 by tvan-bee      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

/*
DESCRIPTION
    The toupper() function converts a lower-case letter to the corresponding
	upper-case letter. The argument must be representable as an unsigned char
	or the value of EOF.

PARAMETERS
	c: The lowercase char that will be converted to uppercase.

RETURN VALUES
    If the argument is a lower-case letter, the toupper() function returns the
	corresponding upper-case letter if there is one; otherwise, the argument is
	returned unchanged.
*/

/*
int	ft_toupper(int c)
{
	// Checks between 'a' and 'z' (see ascii decimal).
	if (c >= 97 && c <= 122)
	{
		// Returns the character in upper-case by decreasing '-32'.
		return (c - 32);
	}
	// Returns given character if char not between 'a' and 'z'.
	return (c);
}
*/

#include "libft.h"

int	ft_toupper(int c)
{
	if (c >= 97 && c <= 122)
	{
		return (c - 32);
	}
	return (c);
}
