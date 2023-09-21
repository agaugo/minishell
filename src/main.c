/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: trstn4 <trstn4@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/08/21 19:24:57 by trstn4        #+#    #+#                 */
/*   Updated: 2023/08/25 13:32:25 by trstn4        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include "../libft/libft.h"

void handle_error(int _exitCode, char *_errorMessage)
{
    perror(_errorMessage);
    exit(_exitCode);
}

// "ctrl-C"
void handle_sigint(int _signalNumber) {
    (void)_signalNumber;  // To silence unused variable warning
    printf("\n");
    rl_on_new_line();     // Notify readline that we have moved to a new line.
    rl_replace_line("", 0);
    rl_redisplay();
}

// "ctrl-\"
void handle_sigquit(int _signalNumber) {
    (void)_signalNumber; 
    // Do nothing
}

void find_and_execute_builtin(struct termios *_oldTermios, char *_userInput)
{
	// if (cmd == "echo")
	// if (cmd == "cd")
	// if (cmd == "pwd")
	// if (cmd == "export")
	// if (cmd == "unset")
	// if (cmd == "env")
    if (ft_strcmp(_userInput, "exit") == 0) {
        exit_cmd(_oldTermios);
    }
}

//RESTORE TERMINAL TO DEFAULT
int restore_terminal(struct termios *_oldTermios) {
  if (tcsetattr(0, TCSANOW, _oldTermios)!= 0){
    perror("tcsetattr");
    return (-1);
  }
  return (0);
}

//INITIALISE SIGNALS
int init_signals(void){
  if (signal(SIGINT, handle_sigint) == SIG_ERR || signal(SIGQUIT, handle_sigquit) == SIG_ERR){
    perror("signal");
    return (-1);
  }
  return (0);
}

//INITIALISE TERMINAL
int init_terminal(struct termios *_oldTermios){
  struct termios _newTermios;
  
  if (tcgetattr(0, _oldTermios) != 0){
    perror("tcgetattr");
    return (-1);                       // Get current terminal settings.
  }
  _newTermios = * _oldTermios;
  _newTermios.c_lflag &= ~ECHOCTL;     // Disable echoing of control chars.
  if (tcsetattr(0, TCSANOW, &_newTermios) != 0) {
    perror("tcsetattr");
    return (-1);
  }                                    // Change terminal settings to new shell.
  return (0);
}

void exit_shell(struct termios *_oldTermios) {
  printf("//exit//\n");
  restore_terminal(_oldTermios);
  exit(0);
}

void process_cmd(char *_userInput, struct termios *_oldTermios) {
  if (!_userInput || !*_userInput)
    return ;
  find_and_execute_builtin(_oldTermios, _userInput);
  add_history(_userInput);
}

int main() {
    char           *_userInput;
    int            _mainLoop;
    struct termios _oldTermios;

    _mainLoop = 1;
    printf(OPEN);
    if (init_terminal(&_oldTermios) == -1)
      handle_error(1, "Failed to initialise shell.");
    if (init_signals() == -1)
        handle_error(1, "Failed to initialise signals.");
    while (_mainLoop) {
       _userInput = readline(PROMPT);
       if (!_userInput)
	 exit_shell(&_oldTermios);
       process_cmd(_userInput, &_oldTermios);
       free(_userInput);
     }
     return (0);
}
