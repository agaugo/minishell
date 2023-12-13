/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   exp_expand.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: trstn4 <trstn4@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/08/21 19:24:57 by trstn4        #+#    #+#                 */
/*   Updated: 2023/12/13 15:32:09 by trstn4        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*ms_expand_exit_code(t_data *data, char *token_value, int *do_free,
			int i)
{
	char	*exit_code_str;
	size_t	cd_len;
	char	*nw_token;

	if ((token_value[i] == '$') && (token_value[i + 1] == '?'))
	{
		exit_code_str = ft_itoa(data->last_exit_code);
		cd_len = ft_strlen(exit_code_str);
		nw_token = (char *)allocate_memory(ft_strlen(token_value) + cd_len + 1);
		ft_strncpy(nw_token, token_value, i);
		ft_strcpy(nw_token + i, exit_code_str);
		ft_strcpy(nw_token + i + cd_len, token_value + i + 2);
		free_memory(exit_code_str);
		*do_free = 1;
		token_value = nw_token;
	}
	return (token_value);
}

char	*ms_expand_tilde(t_data *data, char *token_value)
{
	int		home_index;
	char	*home_path;
	size_t	new_size;
	char	*new_token_value;

	if (token_value[0] == '~' && (token_value[1] == '/'
			|| token_value[1] == '\0'))
	{
		home_index = ms_find_env_index(data->envp, "HOME");
		if (home_index == -1)
		{
			return (ft_strdup(token_value));
		}
		home_path = ft_strchr(data->envp[home_index], '=') + 1;
		new_size = ft_strlen(home_path) + ft_strlen(token_value);
		new_token_value = (char *)allocate_memory(new_size);
		ft_strcpy(new_token_value, home_path);
		ft_strcat(new_token_value, token_value + 1);
		return (new_token_value);
	}
	return (ft_strdup(token_value));
}

char	*ms_expand_dollarsign(t_data *data, char *token_value)
{
	int		index;
	char	*var_val;

	data->last_exit_code = 0;
	index = ms_find_env_index(data->envp, token_value);
	if (index == -1)
		return (ft_strdup(""));
	var_val = ft_strchr(data->envp[index], '=') + 1;
	return (ft_strdup(var_val));
}

void	ms_expand_variable(t_data *data, t_token_t *current_token)
{
	char	*expanded_value;

	expanded_value = ms_call_expand(data, current_token->value);
	free_memory(current_token->value);
	current_token->value = expanded_value;
}

void	ms_expand_tokens(t_data *data, t_token_t *current_token)
{
	char	*expanded_string;

	if (ft_strchr(current_token->value, '~'))
	{
		expanded_string = ms_expand_tilde(data, current_token->value);
		free_memory(current_token->value);
		current_token->value = expanded_string;
	}
	if (ft_strchr(current_token->value, '$'))
	{
		expanded_string = ms_call_expand(data, current_token->value);
		free_memory(current_token->value);
		current_token->value = expanded_string;
	}
}
