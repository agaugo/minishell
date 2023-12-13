/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: trstn4 <trstn4@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/08/21 19:24:57 by trstn4        #+#    #+#                 */
/*   Updated: 2023/12/13 14:29:09 by trstn4        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ms_reset_std(int *std_in, int *std_out)
{
	if (dup2(*std_out, 1) == -1)
		perror("Error restoring standard output");
	if (dup2(*std_in, 0) == -1)
		perror("Error restoring standard output");
	close(*std_out);
	close(*std_in);
}

void	remove_newline(char *str)
{
	size_t	len;

	if (str == NULL)
		return ;
	len = strlen(str);
	if (len > 0 && str[len - 1] == '\n')
		str[len - 1] = '\0';
}

void	ms_check_command(t_data *data)
{
	int		std_out;
	int		std_in;
	char	*heredoc_content;

	std_in = dup(0);
	std_out = dup(1);
	data->redirect = 0;
	if (data->heredoc_tmp_file != NULL)
	{
		heredoc_content = read_file_content(data->heredoc_tmp_file);
		if (heredoc_content)
		{
			free_memory(data->tokens->value);
			data->tokens->value = heredoc_content;
			remove_newline(data->tokens->value);
		}
		unlink(data->heredoc_tmp_file);
		free_memory(data->heredoc_tmp_file);
		data->heredoc_tmp_file = NULL;
	}
	ms_resolve_command_paths(data);
	remove_intermediate_input_redirections(data);
	ms_execute_commands(data);
	ms_reset_std(&std_in, &std_out);
}

void	ms_process_input(t_data *data)
{
	if (!data->user_input || !*data->user_input)
		return ;
	ms_check_command(data);
	add_history(data->user_input);
}

int	main(int argc, char *argv[], char *envp[])
{
	t_data			data;
	struct termios	original_termios;

	if (argc > 1)
	{
		printf("%s: Do not parse any commands yet\n", argv[1]);
		exit(1);
	}
	original_termios = enable_noncanonical_mode();
	data.original_termios = &original_termios;
	if (ms_init_signals() == -1)
		ms_handle_error(1, "Failed to initialise signals.");
	ms_make_data_struct(&data, envp);
	while (1)
	{
		data.user_input = readline(PROMPT);
		ms_handle_ctrl_d(&data);
		data.tokens = ms_tokenizer(data);
		ms_expander(&data);
		if (data.tokens != NULL)
			ms_process_input(&data);
		free_token_list(data.tokens);
		free_memory(data.user_input);
	}
	return (0);
}
