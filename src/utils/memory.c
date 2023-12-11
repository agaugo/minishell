#include "../../includes/minishell.h"
#include <stdlib.h>
#include <stdio.h>

size_t malloc_count = 1;
size_t free_count = 0;

void *allocate_memory(size_t buffer_size) {
    void *buffer;

    buffer = (void *)malloc(buffer_size);
    if (!buffer)
        ms_handle_error(-1, "Error: Malloc failed to allocate memory.");
    
    printf("+ + + MEMORY ALLOCATION -> Malloc #%zu Allocated %zu bytes of memory at %p\n",malloc_count, buffer_size, buffer);
    malloc_count++;

    return buffer;
}

void free_memory(void *buffer) {
    if (buffer) {
        printf("- - - MEMORY FREED -> Free #%zu, Freed memory at %p\n ", free_count, buffer);
        free(buffer);
        buffer = NULL;
        free_count++;
    }
}


void free_token_list(token_t *head) {
    token_t *current = head;
    token_t *next;
    while (current != NULL) {
        next = current->next;
        free_memory(current->value);
        free_memory(current->executableDir);
        free_memory(current); // Free the token itself
        current = next;
    }
}

void wipe_data_struct(data_t *data) {
    if (data == NULL) {
        return;
    }

    // Free any dynamically allocated memory within data
    free_memory(data->user_input);
    free_memory(data->executableDir);
    free_memory(data->heredoc_tmp_file);
    free_memory(data->last_path);
    free_token_list(data->tokens);

    // If data->envp is dynamically allocated and unique to data, free it
    if (data->envp != NULL) {
        char **env = data->envp;
        while (*env != NULL)
		{
            free_memory(*env);
            env++;
        }
        free_memory(data->envp);
    }
    ft_memset(data, 0, sizeof(data_t));
}

void* memory_realloc(void* ptr, size_t new_size) 
{
    void* new_ptr;
    size_t copy_size;

    if (new_size == 0)
	{
        free_memory(ptr);
        return NULL;
    }
    if (ptr == NULL)
        return (allocate_memory(new_size));
    new_ptr = allocate_memory(new_size);
    if (new_ptr != NULL) 
	{
        if (new_size < sizeof(ptr))
            copy_size = new_size;
        else
            copy_size = sizeof(ptr);
        ft_memcpy(new_ptr, ptr, copy_size);
        free_memory(ptr);
    }
    return (new_ptr);
}
