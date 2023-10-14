#include "../../includes/minishell.h"

int checkAbsolutePath(token_t *_token)
{
    if (access(_token->value, X_OK) != -1)
        return (1);
    else
        return (0);
}

void freeTwoDimensionalArray(char **_array)
{
    int _index;

    _index = 0;
    while (_array[_index] != NULL)
    {
        free(_array[_index]);
        _index++;
    }
    free(_array);
}

int validateToken(token_t *_token)
{
    int _index;
    char *_path;
    char **_pathDirectories;
    char *_fullDirectory;

    if (checkAbsolutePath(_token))
        return (1);
    _path = getenv("PATH");
    if (_path == NULL)
    {
        ms_handleError(2, "PATH Variable not set");
        return (0);
    }
    _pathDirectories = ft_split(_path, ':');
    _index = 0;
    while (_pathDirectories[_index] != NULL)
    {
        _fullDirectory = ft_strjoin(_pathDirectories[_index], "/");
        _fullDirectory = ft_strjoin(_fullDirectory, _token->value);
        if (access(_fullDirectory, X_OK) != -1)
        {
            _token->executableDir = _fullDirectory; //THIS NEEDS TO BE FREED SOMEWHERE
            freeTwoDimensionalArray(_pathDirectories);
            return (1);
        }
        free(_fullDirectory);
        _index++;
    }
    //ERROR HANDLING HERE OR IN FUNCTION CALL SYSTEM?
    freeTwoDimensionalArray(_pathDirectories);
    ms_handleError(1, "Invalid Command");
    return (0);
}
