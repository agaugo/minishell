/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   tok_parse_tokens.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: trstn4 <trstn4@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/09/21 13:42:34 by trstn4        #+#    #+#                 */
/*   Updated: 2023/12/13 15:05:30 by trstn4        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_tokentype_t	parse_pipe_token(char **current)
{
	if (**current == '|')
	{
		(*current)++;
		return (T_PIPE);
	}
	return (T_WORD);
}

t_tokentype_t	parse_redirect_token2(char **current)
{
	if (*(*current + 1) != '\0' && *(*current + 1) == '>')
	{
		*current += 2;
		return (T_APPEND_OUT);
	}
	else
	{
		(*current)++;
		return (T_REDIRECT_OUT);
	}
}

t_tokentype_t	parse_redirect_token(char **current)
{
	if (**current == '<')
	{
		if (*(*current + 1) == '<')
		{
			*current += 2;
			return (T_HEREDOC);
		}
		else
		{
			(*current)++;
			return (T_REDIRECT_IN);
		}
	}
	else if (**current == '>')
		return (parse_redirect_token2(current));
	return (T_WORD);
}

t_tokentype_t	parse_quote_token(char **current)
{
	if (**current == '\'')
	{
		(*current)++;
		while (**current != '\'' && **current != '\0')
			(*current)++;
		if (**current == '\'')
			(*current)++;
		return (T_SINGLE_QUOTE);
	}
	else if (**current == '\"')
	{
		(*current)++;
		while (**current != '\"' && **current != '\0')
			(*current)++;
		if (**current == '\"')
			(*current)++;
		return (T_DOUBLE_QUOTE);
	}
	return (T_WORD);
}

t_tokentype_t	parse_word_token(char **current)
{
	while (**current && !ms_is_whitespace(**current) && **current != '|'
		&& **current != '<' && **current != '>' && **current != '\''
		&& **current != '\"')
		(*current)++;
	return (T_WORD);
}
