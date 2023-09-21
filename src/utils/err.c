//
// Created by Hugo Flohil de Sousa on 21/09/2023.
//

#include "../../includes/minishell.h"

void ms_handleError(int _exitCode, char *_errorMessage)
{
    perror(_errorMessage);
    exit(_exitCode);
}
