/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cd.c                                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: trstn4 <trstn4@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/08/25 10:37:37 by trstn4        #+#    #+#                 */
/*   Updated: 2023/08/25 11:19:45 by trstn4        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void addDash(char **_array)
{
    int _index;

    _index = 0;
    _array[0] = ft_strjoin("/", _array[_index]);
    while(_array[_index] != NULL)
    {
        _array[_index] = ft_strjoin(_array[_index], "/");
        _index++;
    }
}

char *glueArray(char **_array)
{
    int _index;
    char *_gluedString;

    _index = 1;
    _gluedString = ft_strdup(_array[0]);
    while(_array[_index] != NULL)
    {
        _gluedString = ft_strjoin(_gluedString, _array[_index]);
        _index++;
    }
    return(_gluedString);
}

void cdCommand(token_t *_token)
{
    char *_PWD;
    char **_arrayPWD;
    char *_newPWD;
    char *_direction;
    int   _index;

    _PWD = getenv("PWD");
    printf("OLD DIRECTORY: %s\n", getCurrentWorkingDirectory());
    _arrayPWD = ft_split(_PWD, '/'); // FIX THIS IT REMOVES THE /
    addDash(_arrayPWD);
    _index = 0;
    _direction = _token->next->value;
    if (ft_strcmp(_direction, "..") == 0)
    {
        while(_arrayPWD[_index + 1] != NULL)
            _index++;
        _arrayPWD[_index] = NULL;
    }
    _newPWD = glueArray(_arrayPWD);
    if (chdir(_newPWD) != 0) {
        handleError(127, "Error finding directory");
    }
    printf("NEW DIRECTORY: %s\n", getCurrentWorkingDirectory());
}
