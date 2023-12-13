/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   stdlib.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: tvan-bee <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/13 13:46:59 by tvan-bee      #+#    #+#                 */
/*   Updated: 2023/12/13 12:37:36 by trstn4        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*ft_strncpy(char *dest, const char *src, size_t n)
{
	char	*dest_start;

	dest_start = dest;
	while (*src != '\0' && n > 0)
	{
		*dest++ = *src++;
		n--;
	}
	while (n > 0)
	{
		*dest++ = '\0';
		n--;
	}
	return (dest_start);
}

char	*ft_strndup(const char *str, size_t n)
{
	char	*result;
	size_t	len;

	if (str == NULL)
		return (NULL);
	len = ft_strlen(str);
	if (n < len)
		len = n;
	result = (char *)allocate_memory(len + 1);
	ft_strncpy(result, str, len);
	result[len] = '\0';
	return (result);
}

char	*ft_strcpy(char *dest, const char *src)
{
	char	*dest_start;

	dest_start = dest;
	while (*src != '\0')
	{
		*dest = *src;
		dest++;
		src++;
	}
	*dest = '\0';
	return (dest_start);
}

char	*ft_strchr(const char *str, int character)
{
	while (*str != '\0')
	{
		if (*str == character)
			return ((char *)str);
		str++;
	}
	return (NULL);
}

char	*ft_strcat(char *dest, const char *src)
{
	char	*dest_start;

	dest_start = dest;
	while (*dest)
		dest++;
	while (*src != '\0')
	{
		*dest = *src;
		dest++;
		src++;
	}
	*dest = '\0';
	return (dest_start);
}
