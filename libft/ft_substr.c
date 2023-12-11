/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_substr.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: tvan-bee <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/13 14:58:00 by tvan-bee      #+#    #+#                 */
/*   Updated: 2022/10/13 15:07:29 by tvan-bee      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

/*
DESCRIPTION
	Allocates (with malloc(3)) and returns a substring from the string ’s’.
	The substring begins at index ’start’ and is of maximum size ’len’.

PARAMETERS
	s: The string from which to create the substring.
	start: The start index of the substring in the string ’s’.
	len: The maximum length of the substring.

RETURN VALUES
	The substring. NULL if the allocation fails.
*/

/*
char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	s_len;
	char	*substr;

	// Returns null if 's' has no value.
	if (!s)
		return (NULL);
	// Assigning string length.
	s_len = ft_strlen(s);
	// Assigns the length of the string to 'len' if the given value is bigger
	// then the string (length - start).
	if (len > s_len - start)
		len = s_len - start;
	// Returns NULL terminator if the 'start' value is equal to the string
	// length.
	if (start >= s_len)
	{
		// Mallocing 1 byte for NULL terminator.
		substr = (char *)malloc(1);
		// Protecting malloc.
		if (!substr)
			return (NULL);
		// Added terminator to the first index.
		substr[0] = '\0';
		// Returns the NULL terminator string
		return (substr);
	}
	// Mallocing space for the substring value.
	substr = (char *)malloc(sizeof(char) * (len + 1));
	// Protecting malloc.
	if (!substr)
		return (NULL);
	// Copies the substring to the 'substr' variable.
	ft_strlcpy(substr, s + start, len + 1);
	// Returns the substring.
	return (substr);
}
*/

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	s_len;
	char	*substr;

	if (!s)
		return (NULL);
	s_len = ft_strlen(s);
	if (len > s_len - start)
		len = s_len - start;
	if (start >= s_len)
	{
		substr = (char *)allocate_memory(1);
		if (!substr)
			return (NULL);
		substr[0] = '\0';
		return (substr);
	}
	substr = (char *)allocate_memory(sizeof(char) * (len + 1));
	if (!substr)
		return (NULL);
	ft_strlcpy(substr, s + start, len + 1);
	return (substr);
}
