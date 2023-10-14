#include "minishell.h"
#include "lexer.h"
#include "parser.h"


// ** src/exe/redirect.c

int     loadFD(token_t *_token, tokentype_t _direction);
void    handleRedirect(token_t *_token, tokentype_t _direction); //so t_direction needs to be set from the previous node, then the node that it is redirected to should be passed here

// ** src/exe/validator.c

void freeTwoDimensionalArray(char **_array);
int checkAbsolutePath(token_t *_token);
int validateToken(token_t *_token);

