/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   export.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: trstn4 <trstn4@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/23 17:46:14 by trstn4        #+#    #+#                 */
/*   Updated: 2023/12/12 15:47:01 by trstn4        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	ms_is_valid_identifier(const char *key)
{
	int	i;

	i = 0;
	if (!key || (!(ft_isalpha(key[0])) && key[0] != '_'))
		return (0);
	while (key[i] && key[i] != '=')
	{
		if (!ft_isalnum(key[i]) && key[i] != '_')
			return (0);
		i++;
	}
	return (1);
}

static char	*create_assignment(char *key, char *value)
{
	char	*new_assignment;

	if (strchr(value, ' ') || strchr(value, '\t') || strchr(value, '\"')
		|| strchr(value, '\''))
	{
		new_assignment = (char *)allocate_memory(strlen(key)
				+ strlen(value) + 4);
		sprintf(new_assignment, "%s=\"%s\"", key, value);
	}
	else
	{
		new_assignment = allocate_memory(strlen(key) + strlen(value) + 2);
		sprintf(new_assignment, "%s=%s", key, value);
	}
	return (new_assignment);
}

static int	find_equals_index(const char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '=')
			return (i);
		i++;
	}
	return (-1);
}

static void	process_token(data_t *data, token_t *current_token)
{
	char	*key;
	char	*value;
	char	*new_assignment;
	int		equals_index;

	key = current_token->value;
	equals_index = find_equals_index(key);
	if (equals_index != -1)
	{
		key[equals_index] = '\0';
	}
	if (!ms_is_valid_identifier(key))
	{
		ft_putendl_fd("minishell: not a valid identifier", STDERR);
		data->last_exit_code = 1;
		return ;
	}
	if (equals_index != -1)
	{
		value = key + equals_index + 1;
		new_assignment = create_assignment(key, value);
		update_env(data, key, new_assignment);
		free_memory(new_assignment);
	}
}

void	ms_export_command(data_t *data, token_t *token)
{
	token_t	*current_token;

	data->last_exit_code = 0;
	current_token = token->next;
	if (!current_token)
	{
		print_env(data);
		return ;
	}
	while (current_token != NULL)
	{
		if (current_token->type == T_PIPE)
			break ;
		process_token(data, current_token);
		current_token = current_token->next;
	}
}
