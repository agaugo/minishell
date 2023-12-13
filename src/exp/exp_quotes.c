/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   exp_quotes.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: trstn4 <trstn4@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/08/21 19:24:57 by trstn4        #+#    #+#                 */
/*   Updated: 2023/12/13 15:33:34 by trstn4        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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
	if (str[*vars->i] == '\'' && !(*vars->in_double_quote))
	{
		*vars->in_single_quote = !(*vars->in_single_quote);
		(*vars->i)++;
	}
	else if (str[*vars->i] == '\"' && !(*vars->in_single_quote))
	{
		*vars->in_double_quote = !(*vars->in_double_quote);
		(*vars->i)++;
	}
	else
		ms_check_quotes2(str, vars);
}

char	*ms_clean_quotes(t_quote_vars *vars, const char *str)
{
	char	*cleaned_str;
	size_t	i;
	size_t	j;
	int		sq;
	int		dq;

	i = 0;
	j = 0;
	sq = 0;
	dq = 0;
	cleaned_str = (char *)allocate_memory(ft_strlen(str) + 1);
	vars = &(t_quote_vars){&i, &j, &sq, &dq, cleaned_str};
	while (str[i])
		ms_check_quotes(str, vars);
	cleaned_str[j] = '\0';
	return (cleaned_str);
}
