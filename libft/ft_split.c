/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_split.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: tvan-bee <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/14 12:11:06 by tvan-bee      #+#    #+#                 */
/*   Updated: 2023/12/13 00:35:38 by trstn4        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

/*
DESCRIPTION
	Allocates (with malloc(3)) and returns an array of strings obtained by
	splitting ’s’ using the character ’c’ as a delimiter. The array must end
	with a NULL pointer.

PARAMETERS
	s: The string to be split.
	c: The delimiter character.

RETURN VALUES
	The array of new strings resulting from the split. NULL if the allocation
	fails.
*/

#include "libft.h"

static void	split_free_memory(char **sub_array, int i)
{
	while (i-- > 0)
	{
		free(sub_array[i]);
	}
	free(sub_array);
}

static int	substr_len(char const *s, char c, int i)
{
	int	len;

	len = 0;
	while (s[i] != c && s[i])
	{
		len++;
		i++;
	}
	return (len);
}

char	**set_array(char const *s, char c, char **sub_array, int total_substr)
{
	int	i;
	int	j;
	int	sub_len;

	i = 0;
	j = -1;
	while (++j < total_substr)
	{
		while (s[i] == c)
			i++;
		sub_len = substr_len(s, c, i);
		sub_array[j] = ft_substr(s, i, sub_len);
		if (!sub_array[j])
		{
			split_free_memory(sub_array, j);
			return (NULL);
		}
		i += sub_len;
	}
	sub_array[j] = 0;
	return (sub_array);
}

static int	substr_count(char const *s, char c)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (s && s[i])
	{
		if (s[i] != c)
		{
			count++;
			while (s[i] != c && s[i])
				i++;
		}
		else
			i++;
	}
	return (count);
}

char	**ft_split(char const *s, char c)
{
	int		total_substr;
	char	**sub_array;

	if (!s)
		return (NULL);
	total_substr = substr_count(s, c);
	sub_array = (char **)malloc(sizeof(char *) * (total_substr + 1));
	if (!sub_array)
		return (NULL);
	sub_array = set_array(s, c, sub_array, total_substr);
	return (sub_array);
}
