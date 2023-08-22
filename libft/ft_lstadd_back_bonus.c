/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_lstadd_back_bonus.c                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: tvan-bee <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/22 12:08:27 by tvan-bee      #+#    #+#                 */
/*   Updated: 2023/05/17 12:08:25 by trstn4        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

/*
DESCRIPTION
	Adds the node ’new’ at the end of the list.

PARAMETERS
	lst: The address of a pointer to the first link of a list.
	new: The address of a pointer to the node to be added to the list.

RETURN VALUES
	None.
*/

/*
void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*last_node;

	// Breaks the function if 'new' parameter has no value.
	if (!new)
		return ;
	// If the first node in the list has no value.
	if (!*lst)
	{
		// Set the first node in the list to the new node.
		*lst = new;
		return ;
	}
	// Links the last node to the new node which makes the new node the last
	// node.
	last_node = ft_lstlast(*lst);
	last_node->next = new;
}
*/

#include "libft.h"

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*last_node;

	if (!new)
		return ;
	if (!*lst)
	{
		*lst = new;
		return ;
	}
	last_node = ft_lstlast(*lst);
	last_node->next = new;
}
