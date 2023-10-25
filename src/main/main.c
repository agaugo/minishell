/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: trstn4 <trstn4@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/08/21 19:24:57 by trstn4        #+#    #+#                 */
/*   Updated: 2023/10/25 15:08:15 by trstn4        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void execute(data_t data)
{
    if (ft_strcmp(data.tokens->value, "export") == 0)
        ms_export_command(data);
    else if (ft_strcmp(data.tokens->value, "unset") == 0)
        ms_unset_command(data);
    else if (ft_strcmp(data.tokens->value, "echo") == 0)
        ms_echo_command(data);
	else if (ft_strcmp(data.tokens->value, "env") == 0)
        ms_print_env_variables(data);
    else if (ft_strcmp(data.tokens->value, "pwd") == 0)
        printf("%s\n", ms_get_current_working_dir());
    else if (ft_strcmp(data.tokens->value, "exit") == 0 || ft_strcmp(data.tokens->value, "EXIT") == 0)
        ms_exit_shell();
    else if (ft_strcmp(data.tokens->value, "cd") == 0)
        ms_cd_command(data);
    else
        ms_identify_command(data.tokens);
}

void processInput(data_t data) {
    if (!data.user_input || !*data.user_input)
        return;
    execute(data);
    add_history(data.user_input);
}

int main(int argc, char *argv[], char *envp[]) {
    data_t  data;
	int			    _mainLoop;
	
	if (argc != 1 || argv[1]) // TO SILENCE WARNING FOR UNUSED VAR
		ms_handle_error(1, "I DONT WANT ANY ARGS PASSED YET!!!");
	printf(OPEN);
    memset(&data, 0, sizeof(data_t)); // Initialize data to zero
	// if (ms_set_terminal_settings(data) == -1)
		// ms_handle_error(1, "Failed to initialise shell.");
	if (ms_init_signals() == -1)
        ms_handle_error(1, "Failed to initialise signals."); //unreachable
	data.envp = ms_clone_envp(envp);
    _mainLoop = 1;
    while (_mainLoop)
    {
        data.user_input = readline(PROMPT);
        ms_handle_ctrl_d(data);
        data.tokens = ms_lexer(data);
        processInput(data);
        free(data.user_input);
    }
	int i = 0;
	while (data.envp[i])
	{
		free(data.envp[i]);
		i++;
	}
	free(data.envp);
	return (0); //unreachable
}
