/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser.h                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: trstn4 <trstn4@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/18 14:32:54 by trstn4        #+#    #+#                 */
/*   Updated: 2023/10/19 12:10:09 by trstn4        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

typedef struct command_node_s {
    char *value;            // Base command (e.g., "ls", "grep")
    char **flags;           // Array of flags (e.g., "-a", "-l")
    char **args;            // Array of arguments, if any
    int flags_count;
    int args_count;
    struct command_node_s *next;
} command_node_t;

#endif
