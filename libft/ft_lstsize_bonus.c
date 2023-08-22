/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_lstsize.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: tvan-bee <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/22 12:07:52 by tvan-bee      #+#    #+#                 */
/*   Updated: 2022/10/22 12:07:57 by tvan-bee      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

/*
DESCRIPTION
	Counts the number of nodes in a list.

PARAMETERS
	lst: The beginning of the list.

RETURN VALUES
	The length of the list.
*/

/*
int	ft_lstsize(t_list *lst)
{
	int	size;

	size = 0;
	// Loops till the terminator is reached in the list.
	while (lst)
	{
		// Continues to the next node and adds the size '+1'.
		lst = lst->next;
		size++;
	}
	// Returns the size/length of the list.
	return (size);
}
*/

#include "libft.h"

int	ft_lstsize(t_list *lst)
{
	int	size;

	size = 0;
	while (lst)
	{
		lst = lst->next;
		size++;
	}
	return (size);
}
