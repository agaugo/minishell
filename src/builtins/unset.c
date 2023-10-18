#include "../../includes/minishell.h"

//refresher on linked lists!

t_envLinkedList *lstAddBack(t_envLinkedList _previous, char *_content)
{

}

t_envLinkedList *convertArrayToLinkedList(char **_array)
{

}

void unsetCommand(token_t *_token)
{
    t_envLinkedList *_head;

    if (!_token->next)
        return ;
    *_head = convertArrayToLinkedList(_token->envp);
}

//CONVERT ENV TO LINKED LIST
//SCAN LIST TO FIND TARGET STRING (TARGET: _TOKEN->NEXT->VALUE
//COMPARE USING FT_STRNCMP: FT_STRNCMP(ENV[I], TARGET, FT_STRLEN(TARGET);
//IF FOUND, DELETE NODE AND REASSIGN -> NEXT