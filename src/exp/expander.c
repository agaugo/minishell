/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   expander.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: trstn4 <trstn4@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/08/21 19:24:57 by trstn4        #+#    #+#                 */
/*   Updated: 2023/12/14 00:54:55 by trstn4        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*ms_expand_more2(t_data *data, t_exp_t_data *exp_data, char *result,
			char *var_name)
{
	char	*var_value;
	int		var_len;

	var_value = ms_expand_dollarsign(data, var_name);
	if (var_value)
	{
		var_len = ft_strlen(var_value);
		ft_strncpy(result + exp_data->j, var_value, var_len);
		exp_data->j += var_len;
		free_memory(var_value);
	}
	else
	{
		result[exp_data->j++] = '$';
		ft_strncpy(result + exp_data->j, var_name, exp_data->k);
		exp_data->j += exp_data->k;
	}
	return (result);
}

char	*ms_expand_more(t_data *data, t_exp_t_data *exp_data, char *token_value,
		char *result)
{
	char	*var_name;

	exp_data->i++;
	exp_data->k = 0;
	var_name = (char *)allocate_memory(ft_strlen(token_value) + 1);
	ft_memset(var_name, 0, ft_strlen(token_value) + 1);
	while (ft_isalnum(token_value[exp_data->i + exp_data->k])
		|| token_value[exp_data->i + exp_data->k] == '_'
		|| token_value[exp_data->i + exp_data->k] == '?')
	{
		var_name[exp_data->k] = token_value[exp_data->i + exp_data->k];
		exp_data->k++;
	}
	var_name[exp_data->k] = '\0';
	if (exp_data->k == 0)
		result[exp_data->j++] = '$';
	else
		result = ms_expand_more2(data, exp_data, result, var_name);
	free_memory(var_name);
	exp_data->i += exp_data->k;
	return (result);
}

char	*ms_call_expand(t_data *data, char *token_value)
{
	char			*result;
	t_exp_t_data	exp_data;

	exp_data.do_free = 0;
	exp_data.i = 0;
	exp_data.j = 0;
	result = allocate_memory(4096);
	while (token_value[exp_data.i])
	{
		token_value = ms_expand_exit_code(data, token_value,
				&exp_data.do_free, exp_data.i);
		if (token_value[exp_data.i] == '$'
			&& token_value[exp_data.i + 1] != '\'')
			result = ms_expand_more(data, &exp_data, token_value, result);
		else
			result[exp_data.j++] = token_value[exp_data.i++];
	}
	result[exp_data.j] = '\0';
	result = memory_realloc(result, exp_data.j + 1);
	if (exp_data.do_free)
		free_memory(token_value);
	return (result);
}

void	process_quotes(t_quote_vars *vars, t_token_t *current_token)
{
	char	*cleaned_string;

	cleaned_string = ms_clean_quotes(vars, current_token->value);
	free_memory(current_token->value);
	current_token->value = cleaned_string;
}

void	ms_expander(t_data *data)
{
	t_token_t			*current_token;
	t_token_t			*prev_token;
	t_quote_vars		vars;

	current_token = data->tokens;
	prev_token = NULL;
	while (current_token)
	{
		if (current_token->type == T_WORD
			|| current_token->type == T_DOUBLE_QUOTE)
		{
			if (current_token->type == T_WORD)
				ms_expand_tokens(data, current_token);
		}
		if (current_token->type == T_DOUBLE_QUOTE)
			ms_expand_variable(data, current_token);
		remove_empty_token(data, &prev_token, &current_token);
		if (!current_token)
			continue ;
		update_token_type(current_token);
		prev_token = current_token;
		current_token = current_token->next;
	}
	merge_connected_tokens(data, &vars);
}
