/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_itoa.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: tvan-bee <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/14 12:05:04 by tvan-bee      #+#    #+#                 */
/*   Updated: 2022/10/14 12:05:06 by tvan-bee      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

/*
DESCRIPTION
	Allocates (with malloc(3)) and returns a string representing the integer
	received as an argument. Negative numbers must be handled.

PARAMETERS
	n: the integer to convert.

RETURN VALUES
	The string representing the integer. NULL if the allocation fails.
*/

/*
static int	count_num_len(int n)
{
	int	count;

	count = 0;
	// Adds room for '-' char if num is negative.
	if (n <= 0)
		count++;
	// Adds the count '+1' for every division.
	while (n && ++count)
		n /= 10;
	// Returns the length of the int.
	return (count);
}

char	*ft_itoa(int n)
{
	int			len;
	char		*char_num;
	const char	*digits = "0123456789";

	// Counts the int length.
	len = count_num_len(n);
	// Mallocs the total int length.
	char_num = (char *)malloc(sizeof(char) * (len + 1));
	// Malloc protection.
	if (!char_num)
		return (NULL);
	// Adds null terminator at the end.
	char_num[len] = '\0';
	// Sets the int to '0' in char if the int is zero.
	if (n == 0)
		char_num[0] = '0';
	// Sets '-' char in first spot if int is negative.
	if (n < 0)
		char_num[0] = '-';
	// Loop until max size reached.
	while (n)
	{
		if (n > 0)
			// If the int is positive, use char string and get the last int
			// in the value using modulus.
			char_num[--len] = n % 10 + '0';
		else
			// If the int is negative, and get the last int in the value
			// using modulus and multiply it by -1 to swap to positive.
			char_num[--len] = n % 10 * -1 + '0';
		// Divides the int by ten.
		n /= 10;
	}
	// Returns the int in char.
	return (char_num);
}
*/

#include "libft.h"
#include "../includes/minishell.h"

static int	count_num_len(int n)
{
	int	count;

	count = 0;
	if (n <= 0)
		count++;
	while (n && ++count)
		n /= 10;
	return (count);
}

char	*ft_itoa(int n)
{
	int			len;
	char		*char_num;

	len = count_num_len(n);
	char_num = (char *)allocate_memory(sizeof(char) * (len + 1));
	if (!char_num)
		return (NULL);
	char_num[len] = '\0';
	if (n == 0)
		char_num[0] = '0';
	if (n < 0)
		char_num[0] = '-';
	while (n)
	{
		if (n > 0)
			char_num[--len] = n % 10 + '0';
		else
			char_num[--len] = n % 10 * -1 + '0';
		n /= 10;
	}
	return (char_num);
}
