#include "../../includes/minishell.h"

void executeCommand(char *_path)
{
    printf("%s", _path);
    //execve();
}

void identifyCommand(token_t *_token)
{
    char *_cmd;
    char *_fullPath;
    char **_allPath;
    int  _index;

    _index = 0;
    _cmd = _token->value;
    _allPath = ft_split(getenv("PATH"), ':');
    while (_allPath[_index] != NULL)
    {
        _allPath[_index] = ft_strjoin(_allPath[_index], "/");
        _fullPath = ft_strjoin(_allPath[_index], _cmd);
        if (access(_fullPath, X_OK) != -1)
            executeCommand(_fullPath);
        _index++;
    }
    perror("Invalid Command");
}
