/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: trstn4 <trstn4@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/08/21 19:24:57 by trstn4        #+#    #+#                 */
/*   Updated: 2023/10/24 23:36:22 by trstn4        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// "ctrl-C"
void handleSigInt(int _signalNumber)
{
	(void)_signalNumber;
	printf("\n");
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

// "ctrl-\"
void handleSigQuit(int _signalNumber) {
	(void)_signalNumber; 
	// Do nothing
}

char **duplicate_envp(char **envp) {
    int count = 0;
    while (envp[count]) count++;

    char **new_envp = malloc(sizeof(char *) * (count + 1));
    if (!new_envp) {
        perror("Failed to allocate memory for new_envp");
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < count; i++) {
        new_envp[i] = strdup(envp[i]);
        if (!new_envp[i]) {
            perror("Failed to duplicate string for new_envp");
            exit(EXIT_FAILURE);
        }
    }
    new_envp[count] = NULL;

    return new_envp;
}

void execute(struct termios *_oldTermios, token_t *_token, char ***cloned_envp_ptr)
{
	// char **dynamic_envp = duplicate_envp(envp);
//  if (ft_strcmp(_token->value, "export") == 0)
//    if (ft_strcmp(_token->value, "unset") == 0)
//        unsetCommand(_token->envp);
    if (ft_strcmp(_token->value, "export") == 0)
        ms_export_command(_token, cloned_envp_ptr);
    else if (ft_strcmp(_token->value, "unset") == 0)
        ms_unset_command(_token, cloned_envp_ptr);
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

//INITIALISE SIGNALS
int initSignals(void){
	if (signal(SIGINT, handleSigInt) == SIG_ERR || signal(SIGQUIT, handleSigQuit) == SIG_ERR){
        handleError(-1, "sigquit");
	}
	return (0);
}

//INITIALISE TERMINAL
int initTerminal(struct termios *_oldTermios){
	struct termios _newTermios;
	
	if (tcgetattr(0, _oldTermios) != 0)
        handleError(-1, "tcgetattr");
	_newTermios = * _oldTermios;
	_newTermios.c_lflag &= ~ECHOCTL;
	if (tcsetattr(0, TCSANOW, &_newTermios) != 0)
        handleError(-1, "tcsetattr");
	return (0);
}

void processInput(char *_userInput, struct termios *_oldTermios, token_t *_token, char ***cloned_envp_ptr) {
    if (!_userInput || !*_userInput)
        return;
    execute(_oldTermios, _token, cloned_envp_ptr);
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
    _mainLoop = 1;
	printf(OPEN);
	if (initTerminal(&_oldTermios) == -1)
		handleError(1, "Failed to initialise shell.");
	if (initSignals() == -1)
        handleError(1, "Failed to initialise signals."); //unreachable
	cloned_envp = duplicate_envp(envp);
    while (_mainLoop)
    {
        _userInput = readline(PROMPT);
        if (!_userInput)
            ms_exit_shell(&_oldTermios);
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
