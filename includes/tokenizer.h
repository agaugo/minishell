/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   tokenizer.h                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: trstn4 <trstn4@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/09/21 18:26:52 by trstn4        #+#    #+#                 */
/*   Updated: 2023/12/13 14:19:37 by trstn4        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKENIZER_H
# define TOKENIZER_H

typedef enum e_tokentype
{
	T_WORD,
	T_PIPE,
	T_REDIRECT_IN,
	T_REDIRECT_OUT,
	T_APPEND_OUT,
	T_HEREDOC,
	T_SINGLE_QUOTE,
	T_DOUBLE_QUOTE,
	T_ENV_VARIABLE,
	T_TILDE
}	tokentype_t;

typedef struct token
{
	char			*value;
	tokentype_t		type;
	struct token	*next;
	int				fd;
	int				status;
	int				connect;
}	token_t;

#endif
