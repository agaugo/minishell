/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: trstn4 <trstn4@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/09/29 12:20:18 by trstn4        #+#    #+#                 */
/*   Updated: 2023/10/12 15:02:51 by trstn4        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void print_tree(tree_node_t *node, int depth)
{
    if (!node) return;

    for(int i = 0; i < depth; i++) 
        printf("--");
//    if(node->token)
//        printf("%s\n", node->token->value);
//    else
//        printf("%d\n", node->operation);
    print_tree(node->left, depth + 1);
    print_tree(node->right, depth + 1);
}

tree_node_t *create_tree_node(token_t *token, tokentype_t operation)
{
    tree_node_t *node = (tree_node_t *)malloc(sizeof(tree_node_t));
    if (!node) return NULL;
    node->token = token;
    node->operation = operation;
    node->left = NULL;
    node->right = NULL;
    return node;
}

tree_node_t *parse_token(token_t **current_token, tokentype_t expected_type)
{
    if (*current_token == NULL || (*current_token)->type != expected_type) return NULL;
    tree_node_t *node = create_tree_node(*current_token, expected_type);
    if (!node) return NULL;
    *current_token = (*current_token)->next;
    return node;
}

tree_node_t *parse_primary(token_t **current_token)
{
    return parse_token(current_token, T_WORD);
}

tree_node_t *parse_operator(token_t **current_token, tokentype_t op_type, tree_node_t *(*parse_lower_precedence)(token_t **))
{
    tree_node_t *node = parse_lower_precedence(current_token);
    while (*current_token && (*current_token)->type == op_type) {
        tree_node_t *op_node = create_tree_node(*current_token, op_type);
        if (!op_node) return NULL;
        op_node->left = node;
        *current_token = (*current_token)->next;
        op_node->right = parse_lower_precedence(current_token);
        node = op_node;
    }
    return node;
}

tree_node_t *parse_pipe(token_t **current_token)
{
    return parse_operator(current_token, T_PIPE, parse_primary);
}

tree_node_t *parse_and(token_t **current_token)
{
    return parse_operator(current_token, T_LOGICAL_AND, parse_pipe);
}

tree_node_t *parse_or(token_t **current_token)
{
    return parse_operator(current_token, T_LOGICAL_OR, parse_and);
}

tree_node_t *parse_expression(token_t **current_token)
{
    return parse_or(current_token);
}

tree_node_t *parse(token_t *head)
{
    tree_node_t *root = NULL;
    if (head == NULL) return NULL;
    root = parse_expression(&head);
    print_tree(root, 0);
    return root;
}
