/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: trstn4 <trstn4@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/08/21 16:42:38 by trstn4        #+#    #+#                 */
/*   Updated: 2023/08/21 16:42:43 by trstn4        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>

int main()
{
	char *input;

    while (1)
	{
        input = readline("minishell$ ");

        if (input && *input) {
            add_history(input);
        }

        free(input);
    }

    return (0);
}
