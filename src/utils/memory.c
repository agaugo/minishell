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

