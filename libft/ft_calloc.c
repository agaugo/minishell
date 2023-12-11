/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_calloc.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: tvan-bee <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/13 11:44:30 by tvan-bee      #+#    #+#                 */
/*   Updated: 2022/10/13 11:44:57 by tvan-bee      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

/*
DESCRIPTION
    The calloc() function allocate memory. The allocated memory is aligned such
	that it can be used for any data type, including AltiVec- and SSE-related
	types.

    The calloc() function contiguously allocates enough space for count objects
	that are size bytes of memory each and returns a pointer to the allocated
	memory. The allocated memory is filled with bytes of value zero.

PARAMETERS
	count: The total bytes of the type.
	size: The total length.

RETURN VALUES
    If successful, calloc() function return a pointer to allocated memory.
	If there is an error, they return a NULL pointer and set errno to ENOMEM.
*/

/*
void	*ft_calloc(size_t count, size_t size)
{
	void *buffer;

	buffer = (void *)malloc(size * count);
	// Protecting malloc.
	if (!buffer)
		return (0);
	// Replaces all characters in 'buffer' with NULL chararcters.
	ft_bzero(buffer, size * count);
	// Returns the updated buffer.
	return ((void *)buffer);
}
*/
#include "../includes/minishell.h"
#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	void	*buffer;

	buffer = (void *)allocate_memory(size * count);
	if (!buffer)
		return (NULL);
	ft_bzero(buffer, size * count);
	return ((void *)buffer);
}
