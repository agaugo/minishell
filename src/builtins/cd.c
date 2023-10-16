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


void cdHome(void)
{
    chdir(getenv("HOME"));
}

void cdAbsolutePath(char *_path)
{
    if (chdir(_path) != 0) {
        handleError(127, "Error finding directory");
    }
}

void cdCommand(token_t *_token)
{
    char *_newPWD;
    char *_direction;

    if (_token->next == NULL)
        return (cdHome());
    _newPWD = NULL;
    _direction = _token->next->value;
    if (access(_direction, F_OK) == 0)
        return (cdAbsolutePath(_direction));
//    else
//        _newPWD = getRelativePath(_PWD, _direction);
    cdAbsolutePath(_newPWD);
}


/*
 ******IGNORE THIS, I COMPLICATED IT TOO MUCH ************
char *getRelativePath(char *_PWD, char *_direction) {
    char **_array;
    int _index;

    _index = 0;
    _array = ft_split(_PWD, '/');
    addDash(_array);
    if (ft_strcmp(_direction, "..") == 0) //modularise this
    {
        while (_array[_index + 1] != NULL)
            _index++;
        _array[_index] = NULL;
    }
    return (glueArray(_array));
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


*/
