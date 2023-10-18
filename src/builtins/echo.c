#include "../../includes/minishell.h"

void echoCommand(token_t *_token)
{
    if (_token->next == NULL)
        printf("\n");
    else
        printf("%s\n", _token->next->value);
}