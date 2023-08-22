/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_putstr_fd.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: tvan-bee <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/14 12:12:45 by tvan-bee      #+#    #+#                 */
/*   Updated: 2022/10/14 12:13:02 by tvan-bee      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

/*
DESCRIPTION
	Outputs the string 's' to the given file descriptor.

PARAMETERS
	s: The string to output.
	fd: The file descriptor on which to write.

RETURN VALUES
	None.
*/

/*
void	ft_putstr_fd(char *s, int fd)
{
	int	i;

	i = 0;
	// Exits the function if 's' has no value.
	if (!s)
		return ;
	while (s[i])
		// Writes the index value with the given file descriptor.
		write(fd, &s[i++], 1);
}
*/

#include <unistd.h>

void	ft_putstr_fd(char *s, int fd)
{
	int	i;

	i = 0;
	if (!s)
		return ;
	while (s[i])
		write(fd, &s[i++], 1);
}
