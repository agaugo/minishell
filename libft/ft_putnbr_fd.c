/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_putnbr_fd.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: tvan-bee <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/14 12:14:03 by tvan-bee      #+#    #+#                 */
/*   Updated: 2022/10/14 12:14:17 by tvan-bee      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

/*
DESCRIPTION
	Outputs the integer 'n' to the given file descriptor.

PARAMETERS
	n: The integer to output.
	fd: The file descriptor on which to write.

RETURN VALUES
	None.
*/

/*
void	ft_putnbr_fd(int n, int fd)
{
	char	c;

	// If the value is equal to the smallest possible int it writes the value with
	// the given file descriptor.
	if (n == -2147483648)
		write(fd, "-2147483648", 11);
	else
	{
		// If the number is negative.
		if (n < 0)
		{
			// Prints the minus and changes and writes the negative value of 'n'
			// with the given file descriptor.
			write(fd, "-", 1);
			n = -n;
			ft_putnbr_fd(n, fd);
		}
		// If the int reaches below value of '10'.
		else if (n < 10)
		{
			// Changes the int value to the value in char type and writes the
			// value with the given file descriptor.
			c = n + '0';
			write(fd, &c, 1);
		}
		// If the value of the int is bigger than '10'.
		else
		{
			// Recalls the function with the int divided by '10'.
			ft_putnbr_fd(n / 10, fd);
			// Writes the value divided by '10' in char type with the given file
			// descriptor.
			c = (n % 10) + '0';
			write(fd, &c, 1);
		}
	}
}
*/

#include "libft.h"

void	ft_putnbr_fd(int n, int fd)
{
	char	c;

	if (n == -2147483648)
		write(fd, "-2147483648", 11);
	else
	{
		if (n < 0)
		{
			write(fd, "-", 1);
			n = -n;
			ft_putnbr_fd(n, fd);
		}
		else if (n < 10)
		{
			c = n + '0';
			write(fd, &c, 1);
		}
		else
		{
			ft_putnbr_fd(n / 10, fd);
			c = (n % 10) + '0';
			write(fd, &c, 1);
		}
	}
}
