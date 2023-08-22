/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_split.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: tvan-bee <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/14 12:11:06 by tvan-bee      #+#    #+#                 */
/*   Updated: 2022/10/14 12:11:59 by tvan-bee      ########   odam.nl         */
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

/*
static void	free_memory(char **sub_array, int i)
{
	// Frees the allocated memory for each index in the array.
	while (i-- > 0)
		free(sub_array[i]);
	// Frees the allocated memory for the array.
	free(sub_array);
}

static int	substr_len(char const *s, char c, int i)
{
	int	len;

	len = 0;
	// Counts the length of the current substring till the split char.
	while (s[i] != c && s[i])
	{
		len++;
		i++;
	}
	// Returns the substr length.
	return (len);
}

char	**set_array(char const *s, char c, char **sub_array, int total_substr)
{
	int	i;
	int	j;
	int	sub_len;

	i = 0;
	j = -1;
	// Loop exists till the count has reached the last index count value.
	while (++j < total_substr)
	{
		// Skips the split char.
		while (s[i] == c)
			i++;
		// Calculates the length of the current substring.
		sub_len = substr_len(s, c, i);
		// Adds the substring to the array using 'substr' function.
		sub_array[j] = ft_substr(s, i, sub_len);
		// If allocation fails, free the memory.
		if (!sub_array[j])
		{
			// Frees the all the memory.
			free_memory(sub_array, j);
			// Malloc protection.
			return (NULL);
		}
		// Continues to the next substring.
		i += sub_len;
	}
	// Ending with NULL terminator.
	sub_array[j] = 0;
	// Returns the substr array.
	return (sub_array);
}

static int	substr_count(char const *s, char c)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	// Counts the total indexes needed for the array.
	while (s && s[i])
	{
		// Split the char and add count '+1' for next substring.
		if (s[i] != c)
		{
			count++;
			// Continues to next substring by passing split char.
			while (s[i] != c && s[i])
				i++;
		}
		// Continue till split char.
		else
			i++;
	}
	// Returns the count of how many substrings there will be.
	return (count);
}

char	**ft_split(char const *s, char c)
{
	int		total_substr;
	char	**sub_array;

	// Returns NULL if 's' has no value.
	if (!s)
		return (NULL);
	// Counts needed substring indexes.
	total_substr = substr_count(s, c);
	// Mallocs the total required indexes in the array.
	sub_array = (char **)malloc(sizeof(char *) * (total_substr + 1));
	// Malloc protection.
	if (!sub_array)
		return (NULL);
	// Sets each index to each splitted string.
	sub_array = set_array(s, c, sub_array, total_substr);
	// Returns the substr array.
	return (sub_array);
}
*/

#include "libft.h"

static void	free_memory(char **sub_array, int i)
{
	while (i-- > 0)
		free(sub_array[i]);
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
			free_memory(sub_array, j);
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
