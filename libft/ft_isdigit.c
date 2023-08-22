/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_isdigit.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: tvan-bee <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/10 16:52:15 by tvan-bee      #+#    #+#                 */
/*   Updated: 2022/10/10 16:52:35 by tvan-bee      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

/*
DESCRIPTION
    The isdigit() function tests for a decimal digit character.  Regardless of
	locale, this includes the following characters only:

    ``0''         ``1''         ``2''         ``3''         ``4''
    ``5''         ``6''         ``7''         ``8''         ``9''

    The value of the argument must be representable as an unsigned char or the
	value of EOF.

PARAMETERS
	c: The char that will be checked.

RETURN VALUES
    The isdigit()function return zero if the character tests false and return
	non-zero if the character tests true.
*/

/*
int	ft_isdigit(int c)
{
	// Checks between '0' and '9' (see ascii decimal).
	if (c >= 48 && c <= 57)
		// True.
		return (1);
	// False.
	return (0);
}
*/

#include "libft.h"

int	ft_isdigit(int c)
{
	if (c >= 48 && c <= 57)
		return (1);
	return (0);
}
