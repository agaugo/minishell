/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   export.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: trstn4 <trstn4@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/23 17:46:14 by trstn4        #+#    #+#                 */
/*   Updated: 2023/12/13 19:04:43 by trstn4        ########   odam.nl         */
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

static char *create_assignment(char *key, char *value)
{
	char *new_assignment;
	size_t key_len = ft_strlen(key);
	size_t value_len = ft_strlen(value);
	size_t total_len;
	size_t i, j;

	if (ft_strchr(value, ' ') || ft_strchr(value, '\t') || ft_strchr(value, '\"') || ft_strchr(value, '\''))
	{
		total_len = key_len + value_len + 4; // Two quotes, equals sign, and null terminator
		new_assignment = (char *)malloc(total_len);
		if (new_assignment == NULL) return NULL; // Memory allocation check

		for (i = 0; key[i] != '\0'; i++)
			new_assignment[i] = key[i];

		new_assignment[i++] = '=';

		new_assignment[i++] = '\"';
		for (j = 0; value[j] != '\0'; j++)
			new_assignment[i + j] = value[j];

		new_assignment[i + j++] = '\"';
		new_assignment[i + j] = '\0'; // Null-terminate the string
	}
	else
	{
		total_len = key_len + value_len + 2; // Equals sign and null terminator
		new_assignment = (char *)malloc(total_len);
		if (new_assignment == NULL) return NULL; // Memory allocation check

		for (i = 0; key[i] != '\0'; i++)
			new_assignment[i] = key[i];

		new_assignment[i++] = '=';
		for (j = 0; value[j] != '\0'; j++)
			new_assignment[i + j] = value[j];

		new_assignment[i + j] = '\0'; // Null-terminate the string
	}

	return new_assignment;
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

static void	process_token(t_data *data, t_token_t *current_token)
{
	char	*key;
	char	*value;
	char	*new_assignment;
	int		equals_index;

	key = current_token->value;
	equals_index = find_equals_index(key);
	if (equals_index != -1)
		key[equals_index] = '\0';
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

void	ms_export_command(t_data *data, t_token_t *token)
{
	t_token_t	*current_token;

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
