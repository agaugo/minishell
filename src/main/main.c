/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: trstn4 <trstn4@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/08/21 19:24:57 by trstn4        #+#    #+#                 */
/*   Updated: 2023/10/25 00:05:31 by trstn4        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void execute(struct termios *_oldTermios, token_t *_token, char ***envp)
{
    if (ft_strcmp(_token->value, "export") == 0)
        ms_export_command(_token, envp);
    else if (ft_strcmp(_token->value, "unset") == 0)
        ms_unset_command(_token, envp);
    else if (ft_strcmp(_token->value, "echo") == 0)
        ms_echo_command(_token);
	else if (ft_strcmp(_token->value, "env") == 0)
        ms_print_env_variables(_token);
    else if (ft_strcmp(_token->value, "pwd") == 0)
        printf("%s\n", ms_get_current_working_dir());
    else if (ft_strcmp(_token->value, "exit") == 0 || ft_strcmp(_token->value, "EXIT") == 0)
        ms_exit_shell(_oldTermios);
    else if (ft_strcmp(_token->value, "cd") == 0)
        ms_cd_command(_token);
    else
        identifyCommand(_token);
}

void processInput(char *_userInput, struct termios *_oldTermios, token_t *_token, char ***envp) {
    if (!_userInput || !*_userInput)
        return;
    execute(_oldTermios, _token, envp);
    add_history(_userInput);
}

int main(int argc, char *argv[], char *envp[]) {
	char		    *_userInput;
	int			    _mainLoop;
	struct	termios _oldTermios;
	token_t         *head = NULL;
	char **cloned_envp = NULL;

	if (argc != 1 || argv[1]) //TO SILENCE WARNING FOR UNUSED VAR
        handleError(1, "I DONT WANT ANY ARGS PASSED YET!!!");
	printf(OPEN);
	if (ms_set_terminal_settings(&_oldTermios) == -1)
		handleError(1, "Failed to initialise shell.");
	if (ms_init_signals() == -1)
        handleError(1, "Failed to initialise signals."); //unreachable
	cloned_envp = duplicate_envp(envp);
    _mainLoop = 1;
    while (_mainLoop)
    {
        _userInput = readline(PROMPT);
        ms_handle_ctrl_d(&_oldTermios, _userInput);
        head = lexer(_userInput, cloned_envp);
        processInput(_userInput, &_oldTermios, head, &cloned_envp);
        free(_userInput);
    }
	int i = 0;
	while (cloned_envp[i])
	{
		free(cloned_envp[i]);
		i++;
	}
	free(cloned_envp);
	return (0); //unreachable
}
