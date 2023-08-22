/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_lstmap.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: tvan-bee <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/22 12:07:43 by tvan-bee      #+#    #+#                 */
/*   Updated: 2022/10/22 12:07:45 by tvan-bee      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

/*
DESCRIPTION
	Iterates the list ’lst’ and applies the function ’f’ on the content of each
	node. Creates a new list resulting of the successive applications of the
	function ’f’. The ’del’ function is used to delete the content of a node if
	needed.

PARAMETERS
	lst: The address of a pointer to a node.
	f: The address of the function used to iterate on the list.
	del: The address of the function used to delete the content of a node if
		needed.

RETURN VALUES
	The new list. NULL if the allocation fails.
*/

/*
t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*head;
	t_list	*node;
	void	*value;

	// Creates the head of the linked list.
	head = NULL;
	// Loops through the parsed linked list.
	while (lst)
	{
		// The new modified value.
		value = f(lst->content);
		// Creates the new node with the modified value.
		node = ft_lstnew(value);
		if (!node)
		{
			// Deletes the newly created modified value.
			del(value);
			// Clears and frees the linked list.
			ft_lstclear(&head, del);
			// Returns null.
			return (NULL);
		}
		// Adds the new list to the back of the linked chain.
		ft_lstadd_back(&head, node);
		// Continues to the next list.
		lst = lst->next;
	}
	// Returns the modified linked list.
	return (head);
}
*/

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*head;
	t_list	*node;
	void	*value;

	head = NULL;
	while (lst)
	{
		value = f(lst->content);
		node = ft_lstnew(value);
		if (!node)
		{
			del(value);
			ft_lstclear(&head, del);
			return (NULL);
		}
		ft_lstadd_back(&head, node);
		lst = lst->next;
	}
	return (head);
}
