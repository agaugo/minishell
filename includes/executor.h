#include "minishell.h"

// ** src/exe/redirect.c

int		ms_load_fd(token_t *_token, tokentype_t _direction);
void	ms_handle_redirect(token_t *_token, tokentype_t _direction);

// ** src/exe/validator.c

void	ms_free_2d_array(char **_array);
int		ms_check_absolute_path(token_t *_token);
int		ms_validate_token(token_t *_token);
