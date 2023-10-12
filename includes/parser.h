/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser.h                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: trstn4 <trstn4@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/09/21 18:26:52 by trstn4        #+#    #+#                 */
/*   Updated: 2023/09/29 23:10:18 by trstn4        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

typedef struct tree_node_t {
    token_t *token;
    tokentype_t operation;
    struct tree_node_t *left, *right;
} tree_node_t;

#endif
