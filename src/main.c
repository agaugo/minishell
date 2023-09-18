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

// "ctrl-C"
void handle_sigint(int signo) {
    (void)signo;  // To prevent unused variable warning
    printf("\n");
    rl_on_new_line(); // Notify readline that we have moved to a new line.
    rl_replace_line("", 0);
    rl_redisplay();
}

// "ctrl-\"
void handle_sigquit(int signo) {
    (void)signo; 
    // Do nothing
}

void find_and_execute_builtin(struct termios *old_termios, char *cmd)
{
	// if (cmd == "echo")
	// if (cmd == "cd")
	// if (cmd == "pwd")
	// if (cmd == "export")
	// if (cmd == "unset")
	// if (cmd == "env")
    if (strcmp(cmd, "exit") == 0) {
        exit_cmd(old_termios);
    }
}

//RESTORE TERMINAL TO DEFAULT
void restore_terminal(struct termios *old_termios) {
  tcsetattr(0, TCSANOW, old_termios);
}

//INITIALISE SIGNALS
void init_signals(void){
  signal(SIGINT, handle_sigint);
  signal(SIGQUIT, handle_sigquit);
}

//INITIALISE TERMINAL
void init_terminal(struct termios *old_termios){
  struct termios new_termios;
  
  tcgetattr(0, old_termios);           // Get current terminal settings.
  new_termios = * old_termios;
  new_termios.c_lflag &= ~ECHOCTL;     // Disable echoing of control chars.
  tcsetattr(0, TCSANOW, &new_termios); //Set terminal to new settings
}

int main() {
    char *cmd;
    struct termios old_termios;

    printf(OPEN);
    init_terminal(&old_termios);
    init_signals();
    while (1) {
       //See minishell.h for prompt definition
       cmd = readline(PROMPT);
       if (!cmd) {
	 printf("exit\n");
	 restore_terminal(&old_termios);
	 exit(0);
       }
       find_and_execute_builtin(&old_termios, cmd);
       if (*cmd) {
	 add_history(cmd);
        }
       free(cmd);
     }
     return (0);
}

