#include "../../includes/minishell.h"

//IF CONTAINING REDIRECTORS > OR < , DUP MUST BE USED BEFORE EXECUTING.

int validateToken(token_t *token)
{
    int i;
    char *dirs[4];
    char *dir;

    dirs[0] = "/bin/";
    dirs[1] = "/usr/bin/";
    dirs[2] = "/usr/local/bin/";
    dirs[3] = NULL;
    i = 0;
    if (!token)
        ms_handleError(1, "Invalid Command");
    while (dirs[i] != NULL)
    {
        dir = ft_strjoin(dirs[i], token->value);
        if (access(dir, X_OK) != -1)
        {
            token->executableDir = dir; //THIS NEEDS TO BE FREED SOMEWHERE
            return (1);
        }
        free(dir);
        i++;
    }
    //ERROR HANDLING HERE OR IN FUNCTION CALL SYSTEM?
    return (0);
}
