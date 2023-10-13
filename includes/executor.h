#include "minishell.h"
#include "lexer.h"
#include "parser.h"

int validateToken(token_t *token);
int loadFD(token_t *_token, tokentype_t _direction);
