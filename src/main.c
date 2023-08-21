/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: trstn4 <trstn4@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/08/21 19:24:57 by trstn4        #+#    #+#                 */
/*   Updated: 2023/08/21 20:24:16 by trstn4        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <termios.h>


// Temporary Colors (soon moves to header file):
// #ifndef _COLOR_H_
// #define _COLOR_H_

# define RESET_COLOR	"\033[0m"
# define BLACK   		"\033[30m"
# define RED     		"\033[31m"
# define LIGHT_RED		"\033[91m"
# define GREEN   		"\033[32m"
# define LIGHT_GREEN	"\033[92m"
# define YELLOW  		"\033[33m"
# define LIGHT_YELLOW	"\033[93m"
# define BLUE    		"\033[34m"
# define LIGHT_BLUE		"\033[94m"
# define MAGENTA 		"\033[35m"
# define LIGHT_MAGENTA	"\033[95m"
# define CYAN    		"\033[36m"
# define LIGHT_CYAN		"\033[96m"
# define WHITE   		"\033[37m"
# define GREY    		"\033[90m"
# define LIGHT_GREY		"\033[37m"

# define BLACK_BOLD   	"\033[1;30m"
# define RED_BOLD     	"\033[1;31m"
# define GREEN_BOLD   	"\033[1;32m"
# define YELLOW_BOLD  	"\033[1;33m"
# define BLUE_BOLD    	"\033[1;34m"
# define MAGENTA_BOLD 	"\033[1;35m"
# define CYAN_BOLD    	"\033[1;36m"
# define WHITE_BOLD   	"\033[1;37m"

# define WELCOME_MSG	"\033[96m╔════════════════════════════════════════════════════════════════════════════════╗\n║                                                                                ║\n║                  \033[95m█▀█ █▀▀ █▀▀   █▀█ █▀█ █▀▀ █▀ █▀▀ █▄░█ ▀█▀ █▀                  \033[96m║\n║                  \033[95m█▀▀ █▀░ █▄▄   █▀▀ █▀▄ ██▄ ▄█ ██▄ █░▀█ ░█░ ▄█                  \033[96m║\n║                                                                                ║\n║      \033[35m ███╗░░░███╗██╗███╗░░██╗██╗░██████╗██╗░░██╗███████╗██╗░░░░░██╗░░░░░       \033[96m║\n║      \033[35m ████╗░████║██║████╗░██║██║██╔════╝██║░░██║██╔════╝██║░░░░░██║░░░░░       \033[96m║\n║     \033[35m  ██╔████╔██║██║██╔██╗██║██║╚█████╗░███████║█████╗░░██║░░░░░██║░░░░░       \033[96m║\n║     \033[35m  ██║╚██╔╝██║██║██║╚████║██║░╚═══██╗██╔══██║██╔══╝░░██║░░░░░██║░░░░░       \033[96m║\n║     \033[35m  ██║░╚═╝░██║██║██║░╚███║██║██████╔╝██║░░██║███████╗███████╗███████╗       \033[96m║\n║      \033[35m ╚═╝░░░░░╚═╝╚═╝╚═╝░░╚══╝╚═╝╚═════╝░╚═╝░░╚═╝╚══════╝╚══════╝╚══════╝       \033[96m║\n║                                                                                ║\n╚════════════════════════════════════════════════════════════════════════════════╝"

# define HEREDOC_MSG	"\033[1;34m> \033[0m"

# define READLINE_MSG	"\033[1;36mminishell\033[34m$ \033[0m"

// #endif



char *get_colored_prompt()
{
	const char* prompt = "minishell$";
	const char* colors[] = {
		RED, GREEN, YELLOW, BLUE, MAGENTA, CYAN, LIGHT_RED, LIGHT_GREEN, LIGHT_BLUE, LIGHT_MAGENTA
	};
		
	char *colored_prompt = malloc(512 * sizeof(char));
	if (!colored_prompt) return NULL;
		
	int offset = 0;
	for (int i = 0; prompt[i]; i++) {
		const char* color = colors[i % (sizeof(colors)/sizeof(colors[0]))];
		while (*color) {
			colored_prompt[offset++] = *color;
			color++;
		}
		colored_prompt[offset++] = prompt[i];
	}
		
	const char *reset = RESET_COLOR;
	while (*reset) {
		colored_prompt[offset++] = *reset;
		reset++;
	}
	colored_prompt[offset++] = ' ';
	colored_prompt[offset] = '\0';

	return colored_prompt;
}

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

    char *prompt = get_colored_prompt();
    if (!prompt) {
        perror("Failed to allocate memory for prompt.");
        return 1;
    }

    while (1) {
		char *input = readline(prompt);
	
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
	free(prompt);
    return (0);
}
