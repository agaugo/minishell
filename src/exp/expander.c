/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: trstn4 <trstn4@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/08/21 19:24:57 by trstn4        #+#    #+#                 */
/*   Updated: 2023/10/25 00:20:21 by trstn4        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"


/*

expand_dollarsign:
- Environment Variables: Recognize patterns like $VAR_NAME or ${VAR_NAME} and replace them with the value of the environment variable.
- Special Variables: Shells often have special variables (e.g., $? to get the exit status of the last command).
- Arithmetic Evaluation: Some shells allow arithmetic expressions, e.g., $((2 + 2)) should expand to 4.

expand_quotes:
- Double Quotes ("): Preserve the literal value of all characters within the quotes, but still allow the expansion of variables. Example: echo "$HOME is your home directory" should expand $HOME but not interpret other characters specially.
- Single Quotes ('): Preserve the literal value of all characters within the quotes. No expansions should occur inside single quotes. Example: echo '$HOME is your home directory' should not expand $HOME.
- Backticks (`): Command substitution. The enclosed command is executed, and the output replaces the backticks expression. Example: `date` should be replaced with the current date.

Tilde Expansion (~):
- Recognize the ~ at the start of a word as a shorthand for the user's home directory.

Brace Expansion:
- Expand expressions like {a,b,c} to a b c. Example: echo {a,b,c}d should produce the output ad bd cd.

Escape Characters: Recognize the backslash \ to escape the next character, making it literal. For instance, \$ should be interpreted as a literal dollar sign, not the start of a variable expansion.


*/

char *expand_dollarsign(data_t data)
{

}

char *expand_quotes(data_t data)
{

}

