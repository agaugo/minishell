/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_putchar_fd.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: tvan-bee <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/14 12:14:46 by tvan-bee      #+#    #+#                 */
/*   Updated: 2022/10/14 12:14:52 by tvan-bee      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

/*
DESCRIPTION
	Outputs the character 'c' to the given file descriptor.

PARAMETERS
	c: The character to output.
	fd: The file descriptor on which to write.

RETURN VALUES
	None.
*/

/*
void	ft_putchar_fd(char c, int fd)
{
	// Writes the character with the given file descriptor.
	write(fd, &c, 1);
}
*/

#include "libft.h"

void	ft_putchar_fd(char c, int fd)
{
	write(fd, &c, 1);
}
