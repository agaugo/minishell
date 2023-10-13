#include "../../includes/minishell.h"

//IF CONTAINING REDIRECTORS > OR < , DUP MUST BE USED BEFORE EXECUTING.

int validateToken(token_t *token)
{
    int _index;
    char *_rootDirectories[4];
    char *_fullDirectory;

    _rootDirectories[0] = "/bin/";
    _rootDirectories[1] = "/usr/bin/";
    _rootDirectories[2] = "/usr/local/bin/";
    _rootDirectories[3] = NULL;
    _index = 0;
    if (!token)
        ms_handleError(1, "Invalid Command");
    while (_rootDirectories[_index] != NULL)
    {
        _fullDirectory = ft_strjoin(_rootDirectories[_index], token->value);
        if (access(_fullDirectory, X_OK) != -1)
        {
            token->executableDir = _fullDirectory; //THIS NEEDS TO BE FREED SOMEWHERE
            return (1);
        }
        free(_fullDirectory);
        _index++;
    }
    //ERROR HANDLING HERE OR IN FUNCTION CALL SYSTEM?
    return (0);
}


