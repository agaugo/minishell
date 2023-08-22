/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_lstlast_bonus.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: tvan-bee <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/22 12:08:18 by tvan-bee      #+#    #+#                 */
/*   Updated: 2023/05/17 12:04:53 by trstn4        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

/*
DESCRIPTION
	Returns the last node of the list.

PARAMETERS
	lst: The beginning of the list.

RETURN VALUES
	Last node of the list.
*/

/*
t_list	*ft_lstlast(t_list *lst)
{
	// Returns NULL if 'lst' has no value.
	if (!lst)
		return (NULL);
	// Loops till the temrinator is reached in the list.
	while (lst->next)
		// Continues to the next node.
		lst = lst->next;
	// Returns the last node from the loop.
	return (lst);
}
*/

#include "libft.h"

t_list	*ft_lstlast(t_list *lst)
{
	if (!lst)
		return (NULL);
	while (lst->next)
		lst = lst->next;
	return (lst);
}
