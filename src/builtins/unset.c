/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   unset.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: trstn4 <trstn4@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/24 19:40:15 by trstn4        #+#    #+#                 */
/*   Updated: 2023/10/25 14:13:08 by trstn4        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void ms_unset_command(data_t data) {
    if (!data.tokens->next) {
        printf("unset: missing argument\n");
        return;
    }

    char *key = data.tokens->next->value;
    int index = find_env_index(data.envp, key);
    
    if (index == -1) {
        printf("unset: %s: not found\n", key);
        return;
    }

    free((data.envp)[index]);

    // Shift the remaining environment variables to fill the gap
    for (int i = index; (data.envp)[i]; i++) {
        (data.envp)[i] = (data.envp)[i + 1];
    }

    // Resize the environment array
    int size;
    for (size = 0; (data.envp)[size]; size++);

    char **new_envp = realloc(data.envp, size * sizeof(char *));
    if (!new_envp) {
        perror("Failed to reallocate memory for envp");
        exit(EXIT_FAILURE);
    }
    
    data.envp = new_envp;
}
