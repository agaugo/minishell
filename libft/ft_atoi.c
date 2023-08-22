/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_atoi.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: tvan-bee <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/10 16:55:21 by tvan-bee      #+#    #+#                 */
/*   Updated: 2022/10/11 11:47:15 by tvan-bee      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

/*
DESCRIPTION
    The atoi() function converts the initial portion of the string pointed to by
	str to int representation.

    It is equivalent to:
    	(int)strtol(str, (char **)NULL, 10);

PARAMETERS
	str: The string that will be converted to an int.

RETURN VALUES
	Returns the integer value of the given integer in char type.
*/

/*
int	ft_atoi(const char *str)
{
	int	i;
	int	sign;
	int	result;

	i = 0;
	sign = 1;
	// Moves the pointer if the index of 'str' is equal between 'ht' and 'cr'
	// (see ascii decimal).
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == 32)
		str++;
	while ((str[i] == '+' || str[i] == '-'))
	{
		// Multiplies the value of 'sign' by '-1' if the index is equal to
		// '-'/minus.
		if (str[i] == '-')
			sign *= -1;
		i++;
	}
	result = 0;
	while (str[i] != '\0' && str[i] >= '0' && str[i] <= '9')
	{
		// Multiplies the current result by '10'.
		// (This is due to add a extra spot for the next integer)
		result *= 10;
		// Adds the index of 'str' in int type by converting it by dividing
		// the value by '0'.
		result += str[i] - '0';
		i++;
	}
	// Swaps the result to 'positive' or 'negative' depending on the value of
	// 'sign'.
	result *= sign;
	// If the second index of 'str' is equal to '+' or '-', return '0'.
	if (str[1] == '+' || str[1] == '-')
		result = 0;
	// Returns result.
	return (result);
}
*/

#include "libft.h"

int	ft_atoi(const char *str)
{
	int	i;
	int	sign;
	int	result;

	i = 0;
	sign = 1;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == 32)
		str++;
	while ((str[i] == '+' || str[i] == '-'))
	{
		if (str[i] == '-')
			sign *= -1;
		i++;
	}
	result = 0;
	while (str[i] != '\0' && str[i] >= '0' && str[i] <= '9')
	{
		result *= 10;
		result += str[i] - '0';
		i++;
	}
	result *= sign;
	if (str[1] == '+' || str[1] == '-')
		result = 0;
	return (result);
}
