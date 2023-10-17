/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: trstn4 <trstn4@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/08/21 19:24:57 by trstn4        #+#    #+#                 */
/*   Updated: 2023/10/12 15:01:26 by trstn4        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include "../libft/libft.h"

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

void executeBuiltin(struct termios *_oldTermios, token_t *_token)
{
//    if (ft_strcmp(_token->value, "echo") == 0)
//    if (ft_strcmp(_token->value, "export") == 0)
//	if (ft_strcmp(_token->value, "unset") == 0)
	if (ft_strcmp(_token->value, "env") == 0)
        printENV(_token);
    if (ft_strcmp(_token->value, "pwd") == 0)
        printf("%s\n", getCurrentWorkingDirectory());
    if (ft_strcmp(_token->value, "exit") == 0 || ft_strcmp(_token->value, "EXIT") == 0)
        exitShell(_oldTermios);
    if (ft_strcmp(_token->value, "cd") == 0)
        cdCommand(_token);
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

void processInput(char *_userInput, struct termios *_oldTermios, token_t *_token) {
	if (!_userInput || !*_userInput)
		return ;
	executeBuiltin(_oldTermios, _token);
	add_history(_userInput);
}

int main(int argc, char *argv[], char *envp[]) {
	char		    *_userInput;
	int			    _mainLoop;
	struct	termios _oldTermios;
	token_t         *head = NULL;

	// tree_node_t *root = NULL;
	if (argc != 1 || argv[1]) //TO SILENCE WARNING FOR UNUSED VAR
        handleError(1, "I DONT WANT ANY ARGS PASSED YET!!!");
    _mainLoop = 1;
	printf(OPEN);
	if (initTerminal(&_oldTermios) == -1)
		handleError(1, "Failed to initialise shell.");
	if (initSignals() == -1)
        handleError(1, "Failed to initialise signals."); //unreachable
	while (_mainLoop)
	{
		_userInput = readline(PROMPT);
		if (!_userInput)
			exitShell(&_oldTermios);
		head = lexer(_userInput, envp);
		parse(head);
		processInput(_userInput, &_oldTermios, head);
		free(_userInput);
	}
	return (0); //unreachable
}
