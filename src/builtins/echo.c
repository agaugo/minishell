/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   echo.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: trstn4 <trstn4@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/23 00:11:40 by trstn4        #+#    #+#                 */
/*   Updated: 2023/11/02 20:32:48 by trstn4        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

typedef struct s_quote_vars
{
	size_t	*i;
	size_t	*j;
	int		*in_single_quote;
	int		*in_double_quote;
	char	*cleaned_str;
}				t_quote_vars;

static void	check_quotes2(const char *str, t_quote_vars *vars)
{
	if ((str[*vars->i] == '\'' || str[*vars->i] == '\"')
		&& !(*vars->in_single_quote) && !(*vars->in_double_quote)
		&& (*vars->i == 0 || *vars->i == strlen(str) - 1
			|| str[*vars->i - 1] == ' ' || str[*vars->i + 1] == ' '
			|| str[*vars->i + 1] == '\0'))
		(*vars->i)++;
	else if (str[*vars->i] == '\'' && str[*vars->i - 1] != ' '
		&& str[*vars->i + 1] != ' ' && !(*vars->in_single_quote)
		&& !(*vars->in_double_quote))
		(*vars->i)++;
	else if (str[*vars->i] == '\"' && str[*vars->i - 1] != ' '
		&& str[*vars->i + 1] == '\"' && !(*vars->in_single_quote)
		&& !(*vars->in_double_quote))
		(*vars->i) += 2;
	else
		vars->cleaned_str[(*vars->j)++] = str[(*vars->i)++];
}

static void	check_quotes(const char *str, t_quote_vars *vars)
{
	if (str[*vars->i] == '\'' && !(*vars->in_double_quote)
		&& (*vars->i == 0 || str[*vars->i - 1] != '\\' || (*vars->i > 1
				&& str[*vars->i - 2] == '\\')))
	{
		*vars->in_single_quote = !(*vars->in_single_quote);
		(*vars->i)++;
	}
	else if (str[*vars->i] == '\"' && !(*vars->in_single_quote)
		&& (*vars->i == 0 || str[*vars->i - 1] != '\\' || (*vars->i > 1
				&& str[*vars->i - 2] == '\\')))
	{
		*vars->in_double_quote = !(*vars->in_double_quote);
		(*vars->i)++;
	}
	else
		check_quotes2(str, vars);
}

static char	*clean_quotes(t_quote_vars *vars, const char *str)
{
	char			*cleaned_str;
	size_t			i;
	size_t			j;
	int				sq;
	int				dq;

	i = 0;
	j = 0;
	sq = 0;
	dq = 0;
	cleaned_str = malloc(strlen(str) + 1);
	vars = &(t_quote_vars){&i, &j, &sq, &dq, cleaned_str};
	while (str[i])
		check_quotes(str, vars);
	cleaned_str[j] = '\0';
	return (cleaned_str);
}

static void	print_echo(data_t *data, char *str)
{
	char	*value;
	int		len;

	if (!data->tokens->next || !data->tokens->next->value)
		printf("\n");
	else if (ft_strcmp(data->tokens->next->value, "-n") == 0)
	{
		if (data->tokens->next->next && data->tokens->next->next->value)
		{
			value = data->tokens->next->next->value;
			len = ft_strlen(value);
			while (len-- > 0 && value[len] == '\n')
				value[len] = '\0';
			printf("%s", value);
		}
	}
	else
		printf("%s\n", str);
}

void	ms_echo_command(data_t *data, token_t *parsed_token)
{
	char			*str;
	char			*cleaned_str;
	token_t			*token;
	char			*temp;
	t_quote_vars	vars;

	str = NULL;
	token = parsed_token;
	while (token)
	{
		cleaned_str = clean_quotes(&vars, token->value);
		if (!str)
			str = cleaned_str;
		else
		{
			temp = ft_strjoin(str, " ");
			free(str);
			str = ft_strjoin(temp, cleaned_str);
			free(temp);
			free(cleaned_str);
		}
		token = token->next;
	}
	print_echo(data, str);
	free(str);
}
