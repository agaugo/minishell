/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: trstn4 <trstn4@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/08/21 19:24:57 by trstn4        #+#    #+#                 */
/*   Updated: 2023/12/06 15:01:35 by trstn4        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// void    print_list3(token_t *head)
// {
//     token_t    *current_token;
//     int        i;

//     current_token = head;
//     i = 0;
//     printf("----------- expander debug -----------------------------------\n");
//     while (current_token)
//     {
//         printf("Token %d: %s, Type: %d\n", i, current_token->value,
//             current_token->type);
//         current_token = current_token->next;
//         i++;
//     }
//     printf("--------------------------------------------------------------\n");
// }

void remove_newline(char *str) {
    if (str == NULL) return;

    size_t len = strlen(str);
    if (len > 0 && str[len - 1] == '\n') {
        str[len - 1] = '\0';
    }
}

char *read_file_content(const char *filename) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        perror("Unable to open file");
        return NULL;
    }

    fseek(file, 0, SEEK_END);
    long length = ftell(file);
    fseek(file, 0, SEEK_SET);

    char *buffer = malloc(length + 1);
    if (!buffer) {
        perror("Memory allocation failed");
        fclose(file);
        return NULL;
    }

    fread(buffer, 1, length, file);
    buffer[length] = '\0';

    fclose(file);
    return buffer;
}

void ms_check_redirect(data_t *data)
{
    token_t *token = data->tokens->next;
    token_t *prev = data->tokens;  // Start with the head's previous node
    token_t *tmp;

    while (token)
    {
        if (token->type == T_REDIRECT_OUT || token->type == T_APPEND_OUT)
        {
            data->redirect = 1;
            ms_redirect(data);
        }
        else if (token->type == T_REDIRECT_IN)
        {
            data->redirect = 2;
            ms_redirect(data);
        }
        else if (token->type == T_HEREDOC)
        {
            ms_heredoc(data, token);

            // Adjust the links in the list before freeing
            tmp = token->next;  // Save the next token
            if (tmp)  // Check if the next token is not NULL
            {
                prev->next = tmp->next;  // Bypass 'token' and 'tmp'
                free(token->value);
                free(token);
                free(tmp->value);
                free(tmp);

                token = prev->next;  // Move to the next valid token
                continue;  // Continue to the next iteration
            }
        }

        prev = token;
        token = token->next;
    }
}

void	ms_reset_std(data_t *data, int *std_in, int *std_out)
{
	if (dup2(*std_out, 1) == -1)
		perror("Error restoring standard output");
	if (dup2(*std_in, 0) == -1)
		perror("Error restoring standard output");
	close(*std_out);
	close(*std_in);
}

void	ms_check_command(data_t *data)
{
	int	std_out;
	int	std_in;

	std_in = dup(0);
	std_out = dup(1);
	data->redirect = 0;
	// ms_check_redir ect(data);

    // int original_stdin = dup(STDIN_FILENO);  // Save the original STDIN

    if (data->heredoc_tmp_file != NULL) {
        char *heredoc_content = read_file_content(data->heredoc_tmp_file);
        if (heredoc_content) {
            // Assign the content to data->tokens->value
            free(data->tokens->value); // Free existing value if necessary
            data->tokens->value = heredoc_content;
			remove_newline(data->tokens->value);
            // Rest of your code to handle the command execution
        }

        // Clean up heredoc file
        unlink(data->heredoc_tmp_file); // Delete the temp file
        free(data->heredoc_tmp_file);
        data->heredoc_tmp_file = NULL;
    }

	// print_list3(data->tokens);

	resolve_command_paths(data);
	ms_execute_commands(data);


    // dup2(original_stdin, STDIN_FILENO);  // Restore the original STDIN
    // close(original_stdin);  // Close the duplicate file descriptor
    
	ms_reset_std(data, &std_in, &std_out);
}

void	ms_process_input(data_t *data)
{
	if (!data->user_input || !*data->user_input)
		return ;
	ms_check_command(data);
	add_history(data->user_input);
}

int	main(int argc, char *argv[], char *envp[])
{
	data_t	data;

	if (argc > 1)
	{
		printf("minishell: %s: Do not parse any commands yet\n", argv[1]);
		exit(1);
	}
	ft_memset(&data, 0, sizeof(data_t));
	if (ms_init_signals() == -1)
		ms_handle_error(1, "Failed to initialise signals.");
	data.envp = ms_clone_envp(envp);
	data.last_exit_code = 0;
	data.heredoc_tmp_file = NULL;
	while (1)
	{
		data.user_input = readline(PROMPT);
		ms_handle_ctrl_d(&data);
		data.tokens = ms_tokenizer(data);
		ms_expander(&data);
        if (data.tokens != NULL)
            ms_process_input(&data);
		free(data.user_input);
	}
	return (0);
}
