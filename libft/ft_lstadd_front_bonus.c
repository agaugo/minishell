/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_lstadd_front.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: tvan-bee <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/22 12:08:36 by tvan-bee      #+#    #+#                 */
/*   Updated: 2022/10/22 12:08:38 by tvan-bee      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

/*
DESCRIPTION
	Adds the node ’new’ at the beginning of the list.

PARAMETERS
	lst: The address of a pointer to the first link of a list.
	new: The address of a pointer to the node to be added to the list.

RETURN VALUES
	None.
*/

/*
void	ft_lstadd_front(t_list **lst, t_list *new)
{
	// Breaks the function if 'new' has no value.
	if (!new)
		return ;
	// Sets the first pointer to the new node if the parameter has no value.
	if (!*lst)
	{
		// Set the first node in the list to the new node.
		*lst = new;
		return ;
	}
	// Sets the first node linking to the new node which now is the first node.
	new->next = *lst;
	// Sets the first pointer to the new first node.
	*lst = new;
}
*/

#include "libft.h"

void	ft_lstadd_front(t_list **lst, t_list *new)
{
	if (!new)
		return ;
	if (!*lst)
	{
		*lst = new;
		return ;
	}
	new->next = *lst;
	*lst = new;
}
