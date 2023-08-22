/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_lstdelone.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: tvan-bee <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/22 12:08:04 by tvan-bee      #+#    #+#                 */
/*   Updated: 2022/10/22 12:08:05 by tvan-bee      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

/*
DESCRIPTION
	Takes as a parameter a node and frees the memory of the node’s content
	using the function ’del’ given as a parameter and free the node. The memory
	of ’next’ must not be freed.

PARAMETERS
	lst: The node to free.
	del: The address of the function used to delete the content.

RETURN VALUES
	None.
*/

/*
void	ft_lstdelone(t_list *lst, void (*del)(void *))
{
	// Breaks the loop if one of the parameters has no value.
	if (!lst || !del)
		return ;
	// Parses the content of the node to the del function.
	del(lst->content);
	// Frees the memory of the node.
	free(lst);
}
*/

#include "libft.h"

void	ft_lstdelone(t_list *lst, void (*del)(void *))
{
	if (!lst || !del)
		return ;
	del(lst->content);
	free(lst);
}
