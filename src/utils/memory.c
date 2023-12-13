/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   memory.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: trstn4 <trstn4@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/08/21 19:24:57 by trstn4        #+#    #+#                 */
/*   Updated: 2023/12/13 12:32:11 by trstn4        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	*allocate_memory(size_t buffer_size)
{
	void	*buffer;

	buffer = (void *)malloc(buffer_size);
	if (!buffer)
		ms_handle_error(-1, "Error: Malloc failed to allocate memory.");
	return (buffer);
}

void	free_memory(void *buffer)
{
	if (buffer)
	{
		free(buffer);
		buffer = NULL;
	}
}

void	free_token_list(token_t *head)
{
	token_t	*current;
	token_t	*next;

	current = head;
	while (current != NULL)
	{
		next = current->next;
		free_memory(current->value);
		free_memory(current);
		current = next;
	}
}

void	wipe_data_struct(data_t *data)
{
	char	**env;

	if (data == NULL)
		return ;
	free_memory(data->user_input);
	free_memory(data->heredoc_tmp_file);
	free_memory(data->last_path);
	free_token_list(data->tokens);
	if (data->envp != NULL)
	{
		env = data->envp;
		while (*env != NULL)
		{
			free_memory(*env);
			env++;
		}
		free_memory(data->envp);
	}
	ft_memset(data, 0, sizeof(data_t));
	if (access("/tmp/minishell_heredoc", F_OK) == 0)
	{
		if (unlink("/tmp/minishell_heredoc") == -1)
			perror("unlink");
	}
}

void	*memory_realloc(void *ptr, size_t new_size)
{
	void	*new_ptr;

	if (new_size == 0)
	{
		free_memory(ptr);
		return (NULL);
	}
	if (ptr == NULL)
		return (allocate_memory(new_size));
	new_ptr = allocate_memory(new_size);
	if (new_ptr == NULL)
		return (NULL);
	ft_memcpy(new_ptr, ptr, new_size);
	free_memory(ptr);
	return (new_ptr);
}
