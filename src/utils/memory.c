#include "../../includes/minishell.h"
#include <stdlib.h>


void	*allocate_memory(size_t buffer_size)
{
    void	*buffer;

    buffer = (void *)malloc(buffer_size);
    if (!buffer)
        ms_handle_error(-1, "Error: Malloc failed to allocate memory.");
    return (buffer);
}

void free_token_list(token_t *head) {
    token_t *current = head;
    token_t *next;
    while (current != NULL) {
        next = current->next;

        // Free the value string in each token
        free(current->value);

        // Free envp if it's dynamically allocated
        // if (current->envp != NULL) {
        //     char **env = current->envp;
        //     while (*env != NULL) {
        //         free(*env);
        //         env++;
        //     }
        //     free(current->envp);
        // }

        // Free executableDir if it's dynamically allocated
        free(current->executableDir);

        // Add any additional fields you want to free here

        free(current); // Free the token itself
        current = next;
    }
}


void wipe_data_struct(data_t *data) {
    if (data == NULL) {
        return;
    }

    // Free any dynamically allocated memory within data
    free(data->user_input);
    free(data->executableDir);
    free(data->heredoc_tmp_file);
    free(data->last_path);
    free_token_list(data->tokens);

    // If data->envp is dynamically allocated and unique to data, free it
    if (data->envp != NULL) {
        char **env = data->envp;
        while (*env != NULL) {
            free(*env);
            env++;
        }
        free(data->envp);
    }

    // Reset the fields to their initial state
    ft_memset(data, 0, sizeof(data_t));
}
