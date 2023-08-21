/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: trstn4 <trstn4@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/08/21 19:24:57 by trstn4        #+#    #+#                 */
/*   Updated: 2023/08/21 19:44:55 by trstn4        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <termios.h>

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

void eof_handler(int count, int key) {
    rl_replace_line("exit", 0);  // Replace current line with "exit"
    rl_redisplay();  // Show the modified line
    printf("\n");  // Move to a new line
    exit(0);
}

int main() {
    char *input;
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
        input = readline("minishell$ ");

        // "ctrl-D"
		if (!input) {
			printf("exit");
			free(input);

			tcsetattr(0, TCSANOW, &old_termios);
			exit(0);
		}

        if (*input) {
            add_history(input);
        }
        free(input);
    }
    return 0;
}
