#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include "../../includes/minishell.h"

char *getCurrentWorkingDirectory(void) {
    char *cwd = NULL;
    size_t size = 1024;  // Initial buffer size

    while (1)
    {
        cwd = (char *)malloc(size);
        if (getcwd(cwd, size) != NULL) {
            return (cwd);
        }
        else
        {
            // If the buffer is too small, try again with a larger buffer
            free(cwd);
            if (errno == ERANGE)
                size *= 2;
            else {
                // Handle other errors, e.g., permission denied
                perror("getcwd");
                return (NULL);
            }
        }
    }
}

