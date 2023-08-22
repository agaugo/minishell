/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strtrim.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: tvan-bee <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/14 12:07:16 by tvan-bee      #+#    #+#                 */
/*   Updated: 2022/10/14 12:07:18 by tvan-bee      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

/*
DESCRIPTION
	Allocates (with malloc(3)) and returns a copy of 's1' with the characters
	specified in 'set' removed from the beginning and the end of the string.

PARAMETERS
	s1: The string to be trimmed.
	set: The reference set of characters to trim.

RETURN VALUES
	The trimmed string. NULL if the allocation fails.
*/

/*
static int	check_set(char c, const char *set)
{
	// Loops through all set chars.
	while (*set)
		// Returns '0' if the current char is equal to the set pointer. 
		if (c == *set++)
			return (0);
	// Returns '1' if the char is not equal to the set pointer.
	return (1);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	start;
	size_t	end;
	char	*strtrim;

	start = 0;
	end = ft_strlen(s1);
	// Returns 'null' if 's1' has no value.
	if (!s1)
		return (NULL);
	// Returns a duplicated value of 's1' if there is no value in 'set'.
	if (!set)
		return (ft_strdup(s1));
	// Adds '+1' to 'start' if the given index is equal to one of 'set' chars.
	while (check_set(s1[start], set) == 0)
		start++;
	// Returns empty string if all chars needs to be trimmed.
	if (start == ft_strlen(s1))
	{
		// Generates empty string.
		strtrim = ft_strdup("");
		// Malloc protection from 'ft_strdup'.
		if (!strtrim)
			return (NULL);
		else
			// Returns empty string.
			return (strtrim);
	}
	// Adds '-1' to 'end' if the given index is equal to one of 'set' chars.
	while (check_set(s1[end - 1], set) == 0)
		end--;
	// Takes the subtring from the string with the known intel.
	strtrim = ft_substr(s1, start, end - start);
	// Returns the trimmed string.
	return (strtrim);
}
*/

#include "libft.h"

static int	check_set(char c, const char *set)
{
	while (*set)
		if (c == *set++)
			return (0);
	return (1);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	start;
	size_t	end;
	char	*strtrim;

	start = 0;
	end = ft_strlen(s1);
	if (!s1)
		return (NULL);
	if (!set)
		return (ft_strdup(s1));
	while (check_set(s1[start], set) == 0)
		start++;
	if (start == ft_strlen(s1))
	{
		strtrim = ft_strdup("");
		if (!strtrim)
			return (NULL);
		else
			return (strtrim);
	}
	while (check_set(s1[end - 1], set) == 0)
		end--;
	strtrim = ft_substr(s1, start, end - start);
	return (strtrim);
}
