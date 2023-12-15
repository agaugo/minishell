/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   exe_heredoc.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: trstn4 <trstn4@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/11/01 16:11:03 by trstn4        #+#    #+#                 */
/*   Updated: 2023/12/15 14:44:34 by trstn4        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ms_handle_heredoc2(t_data *data, t_token_t *temp,
			t_token_t *first_command_token)
{
	t_token_t	*new_token;

	temp->type = T_REDIRECT_IN;
	free_memory(temp->value);
	temp->value = ft_strdup("<");
	if (temp->next)
	{
		temp->next->type = T_WORD;
		free_memory(temp->next->value);
		temp->next->value = ft_strdup(data->heredoc_tmp_file);
		if (first_command_token && first_command_token->type != T_WORD)
		{
			new_token = allocate_memory(sizeof(t_token_t));
			new_token->value = ft_strdup("|");
			new_token->type = T_PIPE;
			new_token->next = temp->next->next;
			new_token->connect = 0;
			temp->next->next = new_token;
			ms_resolve_command_paths(data);
		}
	}
}

t_token_t	*ms_handle_heredoc(t_data *data, t_token_t *temp,
			t_token_t *first_command_token)
{
	while (temp != NULL)
	{
		if (temp->type == T_PIPE)
			first_command_token = temp->next;
		if (temp->type == T_HEREDOC)
		{
			ms_heredoc(data, temp);
			ms_handle_heredoc2(data, temp, first_command_token);
			remove_intermediate_input_redirections(data);
			free_memory(data->heredoc_tmp_file);
			data->heredoc_tmp_file = NULL;
		}
		temp = temp->next;
	}
	return (first_command_token);
}

void	ms_read_heredoc(t_data *data, char *delimiter, int *fd)
{
	char	*input;
	char	*expanded_input;

	while (1)
	{
		input = readline("> ");
		if (!input)
		{
			free_memory(input);
			break ;
		}
		if (ft_strcmp(input, delimiter) == 0)
		{
			free_memory(input);
			break ;
		}
		expanded_input = ms_call_expand(data, input);
		write(*fd, expanded_input, ft_strlen(expanded_input));
		write(*fd, "\n", 1);
		free_memory(expanded_input);
		free_memory(input);
	}
}

void	ms_heredoc(t_data *data, t_token_t *token)
{
	char	*temp_filename;
	int		fd;

	temp_filename = "/tmp/minishell_heredoc";
	if (access(temp_filename, F_OK) == 0)
	{
		if (unlink(temp_filename) == -1)
		{
			perror("unlink");
			return ;
		}
	}
	fd = open(temp_filename, O_RDWR | O_CREAT | O_TRUNC, 0600);
	if (fd == -1)
	{
		ms_handle_error(1, "Failed to open file for heredoc");
		return ;
	}
	data->last_exit_code = 0;
	ms_read_heredoc(data, token->next->value, &fd);
	close(fd);
	data->heredoc_tmp_file = ft_strdup(temp_filename);
}
