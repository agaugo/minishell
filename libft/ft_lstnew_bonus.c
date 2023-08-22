/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_lstnew_bonus.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: tvan-bee <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/22 12:07:32 by tvan-bee      #+#    #+#                 */
/*   Updated: 2023/05/10 11:20:09 by trstn4        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

/*
DESCRIPTION
	Allocates (with malloc(3)) and returns a new node. The member variable
	’content’ is initialized with the value of the parameter ’content’.
	The variable ’next’ is initialized to NULL.

PARAMETERS
	content: The content to create the node with

RETURN VALUES
	The new node.
*/

/*
t_list	*ft_lstnew(void *content)
{
	t_list	*new_list;

	// Allocates the needed memory for t_list node.
	new_list = (t_list *)malloc(sizeof(t_list));
	// Malloc protection.
	if (!new_list)
		return (NULL);
	// Sets the content of the node.
	new_list->content = content;
	// Indicate that next node is end/terminated.
	new_list->next = NULL;
	// Returns the node.
	return (new_list);
}
*/

#include "libft.h"

t_list	*ft_lstnew(void *content)
{
	t_list	*new_list;

	new_list = (t_list *)malloc(sizeof(t_list));
	if (!new_list)
		return (NULL);
	new_list->content = content;
	new_list->next = NULL;
	return (new_list);
}
