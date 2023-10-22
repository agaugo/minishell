#include "../../includes/minishell.h"

void executeCommand(char **_array, char **_envp)
{
    execve(_array[0], _array, _envp);
}

int countArrayLen(token_t *_token)
{
    int     _count;
    token_t *_newToken;

    _count = 0;
    _newToken = _token;
    while (_newToken)
    {
        _newToken = _newToken->next;
        _count++;
    }
    return (_count);
}

char **getFullArgs(token_t *_token)
{
    token_t *_newToken;
    char    **_returnArray;
    int     _index;
    int     _len;

    _len = countArrayLen(_token);
    _index = 0;
    _returnArray = (char **) malloc((_len + 1) * sizeof(char *));
    _returnArray[_len] = NULL;

    _newToken = _token;
    while (_newToken != NULL)
    {
        _returnArray[_index] = ft_strdup(_newToken->value);
        _newToken = _newToken->next;
        _index++;
    }
    return(_returnArray);
}

void identifyCommand(token_t *_token)
{
    char *_cmd;
    char *_fullPath;
    char **_allPath;
    char **_execAll;
    int  _index;

    _index = 0;
    _cmd = _token->value;
    _allPath = ft_split(getenv("PATH"), ':');
    while (_allPath[_index] != NULL)
    {
        _allPath[_index] = ft_strjoin(_allPath[_index], "/");
        _fullPath = ft_strjoin(_allPath[_index], _cmd);
        if (access(_fullPath, X_OK) != -1)
        {
            _execAll = getFullArgs(_token);
            executeCommand(_execAll, _token->envp);
        }
        _index++;
    }
    perror("Invalid Command");
}


