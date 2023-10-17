#include "../../includes/minishell.h"


void printENV(token_t *_token)
{
    char **env;
    int  _index;

    _index = 0;
    env = _token->envp;
    while (env[_index] != NULL)
    {
        printf("%s\n", env[_index]);
        _index++;
    }
}