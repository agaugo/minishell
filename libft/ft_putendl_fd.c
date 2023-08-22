/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_putendl_fd.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: tvan-bee <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/14 12:14:28 by tvan-bee      #+#    #+#                 */
/*   Updated: 2022/10/14 12:14:33 by tvan-bee      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

/*
DESCRIPTION
	Outputs the string 's' to the given file descriptor followed by a newline.

PARAMETERS
	s: The string to output.
	fd: The file descriptor on which to write.

RETURN VALUES
	None.
*/

/*
void	ft_putendl_fd(char *s, int fd)
{
	// Exits the function if 's' has no value.
	if (!s)
		return ;
	while (*s)
		// Writes the pointer value with the given file descriptor.
		write(fd, s++, 1);
	// Writes a newline.
	write(fd, "\n", 1);
}
*/

#include "libft.h"

void	ft_putendl_fd(char *s, int fd)
{
	if (!s)
		return ;
	while (*s)
		write(fd, s++, 1);
	write(fd, "\n", 1);
}
