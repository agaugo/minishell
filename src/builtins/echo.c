/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   echo.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: trstn4 <trstn4@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/23 00:11:40 by trstn4        #+#    #+#                 */
/*   Updated: 2023/11/28 12:10:57 by trstn4        ########   odam.nl         */
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

static void	ms_check_quotes2(const char *str, t_quote_vars *vars)
{
	if ((str[*vars->i] == '\'' || str[*vars->i] == '\"')
		&& !(*vars->in_single_quote) && !(*vars->in_double_quote)
		&& (*vars->i == 0 || *vars->i == ft_strlen(str) - 1
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

static void	ms_check_quotes(const char *str, t_quote_vars *vars)
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
		ms_check_quotes2(str, vars);
}

static char	*ms_clean_quotes(t_quote_vars *vars, const char *str)
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
	cleaned_str = malloc(ft_strlen(str) + 1);
	vars = &(t_quote_vars){&i, &j, &sq, &dq, cleaned_str};
	while (str[i])
		ms_check_quotes(str, vars);
	cleaned_str[j] = '\0';
	return (cleaned_str);
}

static void	ms_print_echo(token_t *token, char *str)
{
	if (!token->next || !token->next->value)
		printf("\n");
	else if (ft_strcmp(token->next->value, "-n") == 0)
	{
		if (token->next->next && token->next->next->value)
		{
			printf("%s", str);
		}
	}
	else
		printf("%s\n", str);
}

void	ms_echo_command(data_t *data, token_t *token)
{
	char			*str;
	char			*cleaned_str;
	char			*temp;
	t_quote_vars	vars;
	token_t *start_token;
	int flag = 0;

	start_token = token;
	str = NULL;
	token = token->next;
	while (token)
	{
		if (token->type == T_PIPE)
			break;
		if (ft_strcmp(token->value, "-n") == 0 && flag == 0)
		{
			token = token->next;
			continue;
		}
		else
			flag = 1;
		cleaned_str = ms_clean_quotes(&vars, token->value);
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
	ms_print_echo(start_token, str);
	free(str);
	data->last_exit_code = 0;
}
