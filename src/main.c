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

int main() {
    char *cmd;
    struct termios old_termios, new_termios;
	
    // Get current terminal settings
    tcgetattr(0, &old_termios);
    new_termios = old_termios;

    // Disable the echoing of control characters
    new_termios.c_lflag &= ~ECHOCTL;

    // Set the terminal to the new settings
    tcsetattr(0, TCSANOW, &new_termios);

    signal(SIGINT, handle_sigint);
    signal(SIGQUIT, handle_sigquit);

    while (1) {
		cmd = readline("\033[1;33mminishell$\033[0m ");

        // "ctrl-D"
		if (!cmd) {
			// rl_replace_line("exit", 0);
    		// rl_redisplay();
			printf("exit\n");
	
			tcsetattr(0, TCSANOW, &old_termios);
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
