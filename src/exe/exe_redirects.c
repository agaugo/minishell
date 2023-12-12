/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   exe_redirects.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: trstn4 <trstn4@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/08/21 19:24:57 by trstn4        #+#    #+#                 */
/*   Updated: 2023/12/13 00:21:26 by trstn4        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int ms_setup_redirection(token_t *tokens)
{
	token_t *current;
	int fd;
	int flags;

	current = tokens;
	while (current != NULL) {
		if (current->type == T_REDIRECT_IN && current->next->type == T_WORD) {
			if (access(current->next->value, F_OK) == -1) {
				fprintf(stderr, "%s: No such file or directory\n", current->next->value);
				return -1; // Return error code for missing input file
			}
			flags = O_RDONLY;
			fd = open(current->next->value, flags);
			if (fd == -1) {
				perror("open");
				return -1;
			}
			dup2(fd, STDIN_FILENO);
			close(fd);
		} else if (current->type == T_REDIRECT_OUT || current->type == T_APPEND_OUT) {
			flags = (current->type == T_APPEND_OUT) ? (O_WRONLY | O_CREAT | O_APPEND) : (O_WRONLY | O_CREAT | O_TRUNC);
			fd = open(current->next->value, flags, 0666);
			if (fd == -1) {
				perror("open");
				return -1;
			}
			dup2(fd, STDOUT_FILENO);
			close(fd);
		}
		current = current->next;
	}
	return 0; // Success
}

token_t *ms_check_redirects(data_t *data, token_t *next_command, int *is_pipe, int *is_redirect, int *br)
{
		while (next_command != NULL) {
			if (next_command->type == T_PIPE) {
				*is_pipe = 1;
				break;
			}
			if (next_command->type == T_REDIRECT_OUT || next_command->type == T_APPEND_OUT ||
				next_command->type == T_REDIRECT_IN) {
				*is_redirect = 1;
				if (next_command->next == NULL || (next_command->next && next_command->next->type != T_WORD))
				{
					char    *val = NULL;
					if (next_command->next == NULL)
						val = "\\n";
					else
						val = next_command->next->value;
					fprintf(stderr, "syntax error near unexpected token '%s'\n", val);
					data->last_exit_code = 258;
					*br = 1;
					break;
				}
			}
			next_command = next_command->next;
		}
		return (next_command);
}
