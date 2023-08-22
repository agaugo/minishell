/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strdup.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: tvan-bee <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/13 13:46:59 by tvan-bee      #+#    #+#                 */
/*   Updated: 2022/10/13 13:47:01 by tvan-bee      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

/*
DESCRIPTION
    The strdup() function allocates sufficient memory for a copy of the string
    s1, does the copy, and returns a pointer to it. The pointer may
    subsequently be used as an argument to the function free(3).

    If insufficient memory is available, NULL is returned and errno is set to
    ENOMEM.

PARAMETERS
	s1: The string that will be duplicated.

RETURN VALUES
    The strdup() function returns the duplicated string.
*/

/*
char	*ft_strdup(const char *s1)
{
	char		*buffer;
	size_t		len;

	// Saves length.
	s1_len = ft_strlen(s1) + 1;
	// Mallocs the given string length.
	buffer = (char *)malloc(sizeof(char) * s1_len);
	// Protecting malloc.
	if (!buffer)
		return (NULL);
	// Copies the string to the buffer using 'memcpy'.
	ft_memcpy(buffer, s1, s1_len);
	// Returns duplicated string.
	return (buffer);
}
*/

#include "libft.h"

char	*ft_strdup(const char *s1)
{
	char		*buffer;
	size_t		s1_len;

	s1_len = ft_strlen(s1) + 1;
	buffer = (char *)malloc(sizeof(char) * s1_len);
	if (!buffer)
		return (NULL);
	ft_memcpy(buffer, s1, s1_len);
	return (buffer);
}
