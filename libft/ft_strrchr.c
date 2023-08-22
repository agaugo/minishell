/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strrchr.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: tvan-bee <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/10 16:33:01 by tvan-bee      #+#    #+#                 */
/*   Updated: 2022/10/10 16:35:32 by tvan-bee      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

/*
DESCRIPTION
    The strchr() function locates the first occurrence of c (converted to a char)
	in the string pointed to by s.  The terminating null character is considered
	to be part of the string; therefore if c is `\0', the functions locate the
	terminating `\0'.

    The strrchr() function is identical to strchr(), except it locates the last
	occurrence of c.

PARAMETERS
	s: The string that will be checked.
	c: The char that needs to be found.

RETURN VALUES
    The function strrchr() return a pointer to the located character, or NULL if
	the character does not appear in the string.
*/

/*
char	*ft_strrchr(const char *s, int c)
{
	int		i;
	char	ch;
	char	*str;
	char	*rtn;

	i = 0;
	ch = (char)c;
	str = (char *)s;
	rtn = 0;
	// Returns null terminator in string.
	if (!ch)
		return (str + ft_strlen(str));
	
	// Loops till index is equal to terminator.
	while (str[i])
	{
		// Assigns each occurrence of the given char to the variable.
		if (str[i] == ch)
			rtn = (str + i);
		i++;
	}
	// Returns the remaining string if the last occurrence of the given char
	// is found in 'str'.
	return (rtn);
}
*/

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int		i;
	char	ch;
	char	*str;
	char	*rtn;

	i = 0;
	ch = (char)c;
	str = (char *)s;
	rtn = 0;
	if (!ch)
		return (str + ft_strlen(str));
	while (str[i])
	{
		if (str[i] == ch)
			rtn = (str + i);
		i++;
	}
	return (rtn);
}
