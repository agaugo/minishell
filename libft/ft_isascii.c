/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_isascii.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: tvan-bee <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/10 16:52:49 by tvan-bee      #+#    #+#                 */
/*   Updated: 2022/10/10 16:53:12 by tvan-bee      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

/*
DESCRIPTION
    The isascii() function tests for an ASCII character, which is any character
	between 0 and octal 0177 inclusive.

PARAMETERS
	c: The char that will be checked.

RETURN VALUES
    The ft_isascii() function return zero if the character tests false and return
	non-zero if the character tests true.
*/

/*
int	ft_isascii(int c)
{
	// Checks between 'nul' and 'del' (see ascii decimal).
	if (c >= 0 && c <= 127)
		// True.
		return (1);
	// False.
	return (0);
}
*/

#include "libft.h"

int	ft_isascii(int c)
{
	if (c >= 0 && c <= 127)
		return (1);
	return (0);
}
