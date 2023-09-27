/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: trstn4 <trstn4@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/08/21 19:24:57 by trstn4        #+#    #+#                 */
/*   Updated: 2023/09/27 13:01:50 by trstn4        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include "../libft/libft.h"

// "ctrl-C"
void ms_handleSigInt(int _signalNumber)
{
		(void)_signalNumber;
		printf("\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
}

// "ctrl-\"
void ms_handleSigQuit(int _signalNumber) {
		(void)_signalNumber; 
		// Do nothing
}

void ms_executeBuiltin(struct termios *_oldTermios, char *_userInput)
{
	// if (cmd == "echo")
	// if (cmd == "cd")
	// if (cmd == "pwd")
	// if (cmd == "export")
	// if (cmd == "unset")
	// if (cmd == "env")
		if (ft_strcmp(_userInput, "exit") == 0) {
				ms_exitShell(_oldTermios);
		}
}

//INITIALISE SIGNALS
int ms_initSignals(void){
	if (signal(SIGINT, ms_handleSigInt) == SIG_ERR || signal(SIGQUIT, ms_handleSigQuit) == SIG_ERR){
		perror("signal");
		return (-1);
	}
	return (0);
}

//INITIALISE TERMINAL
int ms_initTerminal(struct termios *_oldTermios){
	struct termios _newTermios;
	
	if (tcgetattr(0, _oldTermios) != 0){
		perror("tcgetattr");
		return (-1);
	}
	_newTermios = * _oldTermios;
	_newTermios.c_lflag &= ~ECHOCTL;
	if (tcsetattr(0, TCSANOW, &_newTermios) != 0) {
		perror("tcsetattr");
		return (-1);
	}
	return (0);
}

void ms_processInput(char *_userInput, struct termios *_oldTermios) {
	if (!_userInput || !*_userInput)
		return ;
	ms_executeBuiltin(_oldTermios, _userInput);
	add_history(_userInput);
}

int main() {
		char           *_userInput;
		int            _mainLoop;
		struct termios _oldTermios;

		_mainLoop = 1;
		printf(OPEN);
		if (ms_initTerminal(&_oldTermios) == -1)
			ms_handleError(1, "Failed to initialise shell.");
		if (ms_initSignals() == -1)
				ms_handleError(1, "Failed to initialise signals.");
		while (_mainLoop) {
			 _userInput = readline(PROMPT);
			if (!_userInput)
					ms_exitShell(&_oldTermios);
			 lexer(_userInput);
			 ms_processInput(_userInput, &_oldTermios);
			 free(_userInput);
		 }
		 return (0);
}
