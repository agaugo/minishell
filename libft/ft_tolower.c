/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_tolower.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: tvan-bee <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/10 16:28:04 by tvan-bee      #+#    #+#                 */
/*   Updated: 2022/10/10 16:28:43 by tvan-bee      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

/*
DESCRIPTION
    The tolower() function converts an upper-case letter to the corresponding
	lower-case letter.  The argument must be representable as an unsigned char
	or the value of EOF.

PARAMETERS
	c: The uppercase char that will be converted to lowercase.

RETURN VALUES
    If the argument is an upper-case letter, the tolower() function returns the
	corresponding lower-case letter if there is one; other-wise, the argument
	is returned unchanged.
*/

/*
int	ft_tolower(int c)
{
	// Checks between 'A' and 'Z' (see ascii decimal).
	if (c >= 65 && c <= 90)
	{
		// Returns the character in lower-case by increasing '+32'.
		return (c + 32);
	}
	// Returns given character if char not between 'A' and 'Z'.
	return (c);
}

*/

#include "libft.h"

int	ft_tolower(int c)
{
	if (c >= 65 && c <= 90)
	{
		return (c + 32);
	}
	return (c);
}
