#include "../../includes/minishell.h"
#include "../../includes/lexer.h"
#include <fcntl.h>
//for pipe, we need the token being reidrected TO, so not the token containing the actual REDIRECT TYPE.
//if  we use it in that way, reimplementation is not that hard we just need to scan token list, and need to know direction.

int loadFD(token_t *_token, tokentype_t _direction)
{
    int _FD;

    if (_direction == T_REDIRECT_IN)
    {
        _FD = open(_token->value, O_RDONLY, 0666);
        if (_FD == -1)
            ms_handleError(1, "Unable to Open Input File");
    }
    if (_direction == T_REDIRECT_OUT)
    {
        _FD = open(_token->value, O_WRONLY | O_CREAT | O_TRUNC, 0666);
        if (_FD == -1)
            ms_handleError(1, "Unable to Open Input File");
    }
    return (_FD);
}

void    handleRedirect(token_t *_token, tokentype_t _direction) //so t_direction needs to be set from the previous node, then the node that it is redirected to should be passed here
{
    int _pipe[2];
    int _FD;
    //int _processID;
    if (pipe(_pipe) == -1)
        ms_handleError(2, "Pipe Creation Error.");
    _FD = loadFD(_token, _direction); 
    if (_direction == T_REDIRECT_IN) //redirect in (read)
    {
        if (dup2(_FD, 0) == -1)
            ms_handleError(2, "Error Redirecting Input to FD");
        if (dup2(_pipe[1], 1) == -1)
            ms_handleError(2, "Error Redirecting out to Pipe");
    }
    if (_direction == T_REDIRECT_OUT) //redirect out (write)
     {
        if (dup2(_FD, 1) == -1)
            ms_handleError(2, "Error Redirecting Output to FD");
        if (dup2(_pipe[0], 0) == -1)
            ms_handleError(2, "Error Redirecting In to Pipe");
    }
    _token->_pipe = _pipe;
    //THIS DOES NOT WORK FOR REDIRECT IN AND OUT
}
