/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_bzero.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: tvan-bee <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/11 14:03:23 by tvan-bee      #+#    #+#                 */
/*   Updated: 2022/10/11 14:03:36 by tvan-bee      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

/*
DESCRIPTION
    The bzero() function writes n zeroed bytes to the string s.  If n is
    zero, bzero() does nothing.

PARAMETERS
	s: The allocated memory variable.
	n: The total length of the variable that will be replaced with NULL bytes.

RETURN VALUES
	None.
*/

/*
void	ft_bzero(void *s, size_t n)
{
	// Calls memset that replaces the given length with the '\0' character(s).
	ft_memset(s, '\0', n);
}
*/

#include "libft.h"

void	ft_bzero(void *s, size_t n)
{
	ft_memset(s, '\0', n);
}
