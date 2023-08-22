/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_lstiter.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: tvan-bee <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/22 12:08:11 by tvan-bee      #+#    #+#                 */
/*   Updated: 2022/10/22 12:08:14 by tvan-bee      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

/*
DESCRIPTION
	Iterates the list ’lst’ and applies the function ’f’ on the content of each
	node.

PARAMETERS
	lst: The address of a pointer to a node.
	f: The address of the function used to iterate on the list.

RETURN VALUES
	None.
*/

/*
void	ft_lstiter(t_list *lst, void (*f)(void *))
{
	// Breaks function if 'f' has no value.
	if (!f)
		return ;
	// Loops till the temrinator is reached in the list.
	while (lst)
	{
		// Parses the content of the node to the function.
		f(lst->content);
		// Continues to the next node.
		lst = lst->next;
	}
}
*/

#include "libft.h"

void	ft_lstiter(t_list *lst, void (*f)(void *))
{
	if (!f)
		return ;
	while (lst)
	{
		f(lst->content);
		lst = lst->next;
	}
}
