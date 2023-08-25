/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: trstn4 <trstn4@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/08/21 19:24:57 by trstn4        #+#    #+#                 */
/*   Updated: 2023/08/25 11:10:39 by trstn4        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/colors.h"
#include "../includes/minishell.h"

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

void find_and_execute_builtin(char *cmd)
{
	printf("%s\n", cmd);
	// if (cmd == "echo")

	// else if (cmd == "cd")

	// else if (cmd == "pwd")

	// else if (cmd == "export")
	
	// else if (cmd == "unset")
	
	// else if (cmd == "env")

	// else if (cmd == "exit")
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

    char *prompt = get_colored_prompt();
    if (!prompt) {
        perror("Failed to allocate memory for prompt.");
        return 1;
    }

    while (1) {
		cmd = readline(prompt);
	
		find_and_execute_builtin(cmd);

        // "ctrl-D"
		if (!cmd) {
			printf("exit");
			free(cmd);

			tcsetattr(0, TCSANOW, &old_termios);
			exit(0);
		}

        if (*cmd) {
            add_history(cmd);
        }
        free(cmd);
    }
	free(prompt);
    return (0);
}
