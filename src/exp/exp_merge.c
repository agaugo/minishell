/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   exp_merge.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: trstn4 <trstn4@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/08/21 19:24:57 by trstn4        #+#    #+#                 */
/*   Updated: 2023/12/13 11:32:58 by trstn4        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*merge_token_values(token_t *current, token_t *next)
{
	size_t	merged_length;
	char	*merged_value;

	merged_length = strlen(current->value) + strlen(next->value);
	merged_value = (char *)allocate_memory(merged_length + 1);
	strcpy(merged_value, current->value);
	strcat(merged_value, next->value);
	return (merged_value);
}

void	merge_connected_tokens(data_t *data)
{
	token_t	*current;
	char	*merged_value;

	if (data == NULL || data->tokens == NULL)
		return ;
	current = data->tokens;
	while (current != NULL && current->next != NULL)
	{
		if (current->connect == 1)
		{
			merged_value = merge_token_values(current, current->next);
			free_memory(current->value);
			current->value = merged_value;
			current->connect = current->next->connect;
			remove_next_token(current);
		}
		else
			current = current->next;
	}
}
