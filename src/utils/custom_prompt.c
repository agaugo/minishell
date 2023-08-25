/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   custom_prompt.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: trstn4 <trstn4@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/08/25 11:15:44 by trstn4        #+#    #+#                 */
/*   Updated: 2023/08/25 11:15:57 by trstn4        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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
