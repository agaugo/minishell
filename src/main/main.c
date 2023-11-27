/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: trstn4 <trstn4@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/08/21 19:24:57 by trstn4        #+#    #+#                 */
/*   Updated: 2023/11/27 11:07:28 by trstn4        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ms_check_redirect(data_t *data)
{
	token_t	*token;

	token = data->tokens->next;
	while (token)
	{
		if (token->type == T_REDIRECT_OUT || token->type == T_APPEND_OUT)
		{
			data->redirect = 1;
			ms_redirect(data);
		}
		else if (token->type == T_REDIRECT_IN)
		{
			data->redirect = 2;
			ms_redirect(data);
		}
		else if (token->type == T_HEREDOC)
			ms_heredoc(token);
		token = token->next;
	}
	return ;
}

void	ms_reset_std(data_t *data, int *std_in, int *std_out)
{
	if (data->redirect == 1)
	{
		if (dup2(*std_out, 1) == -1)
			perror("Error restoring standard output");
		if (dup2(*std_in, 0) == -1)
			perror("Error restoring standard output");
		close(*std_out);
		close(*std_in);
	}
}

void	ms_check_command(data_t *data)
{
	int	std_out;
	int	std_in;

	std_in = dup(0);
	std_out = dup(1);
	data->redirect = 0;
	ms_check_redirect(data);
    // ms_check_pipe(data);
    if (ft_strcmp(data->tokens->value, "export") == 0)
		ms_export_command(data);
	else if (ft_strcmp(data->tokens->value, "unset") == 0)
		ms_unset_command(data);
	else if (ft_strcmp(data->tokens->value, "echo") == 0)
		ms_echo_command(data, data->tokens->next);
	else if (ft_strcmp(data->tokens->value, "env") == 0)
		ms_print_env_variables(data);
	else if (ft_strcmp(data->tokens->value, "pwd") == 0)
		ms_pwd_command(data);
	else if (ft_strcmp(data->tokens->value, "exit") == 0
		|| ft_strcmp(data->tokens->value, "EXIT") == 0)
		ms_exit_shell(data, data->tokens->next);
	else if (ft_strcmp(data->tokens->value, "cd") == 0)
		ms_cd_command(data);
	else
	{
		resolve_command_paths(data);
		ms_execute_commands(data);
	}
		// ms_identify_command(data);
	ms_reset_std(data, &std_in, &std_out);
}

void	ms_process_input(data_t *data)
{
	if (!data->user_input || !*data->user_input)
		return ;
	ms_check_command(data);
	add_history(data->user_input);
}

int	main(int argc, char *argv[], char *envp[])
{
	data_t	data;

	if (argc > 1)
	{
		printf("minishell: %s: Do not parse any commands yet\n", argv[1]);
		exit(1);
	}
	ft_memset(&data, 0, sizeof(data_t));
	if (ms_init_signals() == -1)
		ms_handle_error(1, "Failed to initialise signals.");
	data.envp = ms_clone_envp(envp);
	data.last_exit_code = 0;
	while (1)
	{
		data.user_input = readline(PROMPT);
		ms_handle_ctrl_d(&data);
		data.tokens = ms_tokenizer(data);
		ms_expander(&data);
		ms_process_input(&data);
		free(data.user_input);
	}
	return (0);
}
