/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strmapi.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: tvan-bee <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/14 12:10:11 by tvan-bee      #+#    #+#                 */
/*   Updated: 2022/10/14 12:10:22 by tvan-bee      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

/*
DESCRIPTION
	Applies the function 'f' to each character of the string 's', and passing
	its index as first argument to create a new string (with malloc(3))
	resulting from successive applications of 'f'.

PARAMETERS
	s: The string on which to iterate.
	f: The function to apply to each character.

RETURN VALUES
	The string created from the successive applicationsof 'f'.
	Returns NULL if the allocation fails.
*/

/*
char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char	*buffer;
	int		len;
	int		i;

	i = 0;
	// If 's' has no value it returns null.
	if (!s)
		return (NULL);
	len = ft_strlen(s);
	buffer = (char *)malloc(sizeof(char) * (len + 1));
	// Returns null if the allocation fails.
	if (!buffer)
		return (NULL);
	while (i < len)
	{ 
		// Applies the function 'f' to each character of the string 's'.
		buffer[i] = f(i, s[i]);
		i++;
	}
	// Adds terminators at the end of the string.
	buffer[len] = '\0';
	// Returns value.
	return (buffer);
}
*/

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char	*buffer;
	int		len;
	int		i;

	i = 0;
	if (!s)
		return (NULL);
	len = ft_strlen(s);
	buffer = (char *)allocate_memory(sizeof(char) * (len + 1));
	if (!buffer)
		return (NULL);
	while (i < len)
	{
		buffer[i] = f(i, s[i]);
		i++;
	}
	buffer[len] = '\0';
	return (buffer);
}
