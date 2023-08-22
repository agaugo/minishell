/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_striteri.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: tvan-bee <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/14 12:10:36 by tvan-bee      #+#    #+#                 */
/*   Updated: 2022/10/14 12:10:54 by tvan-bee      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

/*
DESCRIPTION
	Applies the function 'f' on each character of the string passed as argument,
	passing its index as first argument. Each character is passed by address to
	'f' to be modified if necessary.

PARAMETERS
	s: The string on which to iterate.
	f: The function to apply to each character.

RETURN VALUES
	None.
*/

/*
void	ft_striteri(char *s, void (*f)(unsigned int, char *))
{
	unsigned int	i;

	// Breaks function if parameters has no value.
	if (!s || !f)
		return ;
	i = 0;
	// Loop until max size reached.
	while (s[i])
	{
		// Applies the function 'f' on each character of the string. 
		f(i, s + i);
		i++;
	}
}
*/

#include "libft.h"

void	ft_striteri(char *s, void (*f)(unsigned int, char *))
{
	unsigned int	i;

	if (!s || !f)
		return ;
	i = 0;
	while (s[i])
	{
		f(i, s + i);
		i++;
	}
}
