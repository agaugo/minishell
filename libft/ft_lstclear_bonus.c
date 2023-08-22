/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_lstclear.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: tvan-bee <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/22 12:08:46 by tvan-bee      #+#    #+#                 */
/*   Updated: 2022/10/22 12:08:47 by tvan-bee      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

/*
DESCRIPTION
	Deletes and frees the given node and every successor of that node, using
	the function ’del’ and free(3). Finally, the pointer to the list must be
	set to NULL.

PARAMETERS
	lst: The address of a pointer to a node.
	del: The address of the function used to delete the content of the node.

RETURN VALUES
	None.
*/

/*
void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*node;

	// Function breaks if the first node in the list has no value.
	if (!*lst)
		return ;
	// Loops till the terminator is reached in the list.
	while (*lst)
	{
		// Assigns the next node.
		node = (*lst)->next;
		// Deletes the current node using 'ft_lstdelone' function.
		ft_lstdelone(*lst, del);
		// Moves to the next node.
		*lst = node;
	}
	// Sets the list to NULL.
	*lst = NULL;
}
*/

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*node;

	if (!*lst)
		return ;
	while (*lst)
	{
		node = (*lst)->next;
		ft_lstdelone(*lst, del);
		*lst = node;
	}
	*lst = NULL;
}
