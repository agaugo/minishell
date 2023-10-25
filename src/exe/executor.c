#include "../../includes/minishell.h"

void executeCommand(char **_array, char **_envp) {
    pid_t pid;

    pid = fork();  // Create a child process
    if (pid == -1) // Fork failed
	{
		freeTwoDimensionalArray(_array);
        handleError(EXIT_FAILURE, "Fork Failure");
	}
    else if (pid == 0) // In child process
    {
        execve(_array[0], _array, _envp);
		freeTwoDimensionalArray(_array);
        handleError(EXIT_FAILURE, "Execve Failure"); //will only run if execve fails
    }
    else {
        wait(NULL);  // Wait for child process to finish
    }
	freeTwoDimensionalArray(_array);
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

char **getFullArgs(token_t *_token, char *_fullPath)
{
    char    **_returnArray;
    int     _index;
    int     _len;

    _len = countArrayLen(_token);
    _index = 0;
    _returnArray = (char **) malloc((_len + 1) * sizeof(char *));
    _returnArray[_len] = NULL;
    _token = _token->next;
    _returnArray[_index] = ft_strdup(_fullPath);
    _index++;
    while (_token != NULL)
    {
        _returnArray[_index] = ft_strdup(_token->value);
        _token = _token->next;
        _index++;
    }
    return(_returnArray);
}

int customExec(token_t *_token, char *_cmd)
{
    char **_execAll;

    if (ft_strchr(_cmd, '/'))
    {
        if (access(_cmd, X_OK) != -1)
        {
            _execAll = getFullArgs(_token, _cmd);
            executeCommand(_execAll, _token->envp);
        }
        else
            perror("No such file or Directory");
        return (1);
    }
    return (-1);
}

void identifyCommand(token_t *_token)
{
    char *_cmd;
    char *_fullPath;
    char **_allPath;
    char **_execAll;
    int  _index;

    _cmd = _token->value;
    if (customExec(_token, _cmd) == 1)
        return ;
    _allPath = ft_split(getenv("PATH"), ':');
    _index = 0;
    while (_allPath[_index] != NULL)
    {
        _allPath[_index] = ft_strjoin(_allPath[_index], "/");
        _fullPath = ft_strjoin(_allPath[_index], _cmd);
        if (access(_fullPath, X_OK) != -1)
        {
            _execAll = getFullArgs(_token, _fullPath);
            executeCommand(_execAll, _token->envp);
            return ;
        }
        _index++;
    }
    perror("Invalid Command");
}
