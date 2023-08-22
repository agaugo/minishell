/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strnstr.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: tvan-bee <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/11 17:52:15 by tvan-bee      #+#    #+#                 */
/*   Updated: 2022/10/11 17:52:52 by tvan-bee      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

/*
DESCRIPTION
    The strnstr() function locates the first occurrence of the null-terminated
	string needle in the string haystack, where not more than len characters
	are searched. Characters that appear after a `\0' character are not
	searched. Since the strnstr() function is a FreeBSD specific API, it should
	only be used when portability is not a concern.

PARAMETERS
	haystack: The string that will be checked.
	needle: The string that needs to be found.
	len: The maximum length that will be checked.

RETURN VALUES
    If needle is an empty string, haystack is returned; if needle occurs
	nowhere in haystack, NULL is returned; otherwise a pointer to the first
	character of the first occurrence of needle is returned.
*/

/*
char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	h;
	size_t	n;

	h = 0;
	// Returns full 'haystack' string if first index is NULL terminator.
	if (needle[0] == '\0')
		return ((char *)haystack);
	// Loop until terminator is reached.
	while (haystack[h])
	{
		n = 0;
		// Loops as long as the index in both parameters are the same and
		// are smaller than the given length.
		while (haystack[h + n] == needle[n] && (h + n) < len)
		{
			// Returns the founded string with the remaining string if the
			// compared characters are the same until both have a terminator
			// character.
			if (haystack[h + n] == '\0' && needle[n] == '\0')
				return ((char *)haystack + h);
			n++;
		}
		// Returns the founded string with the remaining string if the
		// compared characters are the same until 'needle' has a terminator
		// character.
		if (needle[n] == '\0')
			return ((char *)haystack + h);
		h++;
	}
	// Returns NULL.
	return (NULL);
}
*/

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	h;
	size_t	n;

	h = 0;
	if (needle[0] == '\0')
		return ((char *)haystack);
	while (haystack[h])
	{
		n = 0;
		while (haystack[h + n] == needle[n] && (h + n) < len)
		{
			if (haystack[h + n] == '\0' && needle[n] == '\0')
				return ((char *)haystack + h);
			n++;
		}
		if (needle[n] == '\0')
			return ((char *)haystack + h);
		h++;
	}
	return (NULL);
}
