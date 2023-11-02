/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   export.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: trstn4 <trstn4@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/23 17:46:14 by trstn4        #+#    #+#                 */
/*   Updated: 2023/11/02 21:09:25 by trstn4        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	ms_is_valid_identifier(const char *key)
{
	int	has_equal_sign;
	int	in_quotes;
	int	i;

	if (!key || (!ft_isalpha(key[0]) && key[0] != '_'))
		return (0);
	has_equal_sign = 0;
	in_quotes = 0;
	i = 1;
	while (key[i])
	{
		if (key[i] == '\"' || key[i] == '\'')
			in_quotes = !in_quotes;
		if (!in_quotes && key[i] == '=' && has_equal_sign++)
			return (0);
		if (!in_quotes && !ft_isalnum(key[i]) && key[i] != '_' && key[i] != '=')
			return (0);
		i++;
	}
	return (1);
}

static int	ms_get_env_size(char **envp)
{
	int	size;

	size = 0;
	while (envp[size])
		size++;
	return (size);
}

static void	ms_add_to_env(data_t *data, char *key)
{
	char	**new_envp;
	int		size;

	size = ms_get_env_size(data->envp);
	new_envp = realloc(data->envp, (size + 2) * sizeof(char *));
	if (!new_envp)
	{
		perror("Failed to reallocate memory for envp");
		exit(EXIT_FAILURE);
	}
	new_envp[size] = ft_strdup(key);
	new_envp[size + 1] = NULL;
	data->envp = new_envp;
}

void	ms_export_command(data_t *data)
{
	char	*key;
	int		i;

	if (!data->tokens->next)
	{
		i = 0;
		while (data->envp[i])
			printf("%s\n", data->envp[i++]);
	}
	else
	{
		key = data->tokens->next->value;
		if (!ms_is_valid_identifier(key))
		{
			fprintf(stderr, "export: `%s': not a valid identifier\n", key);
			data->last_exit_code = 1;
		}
		else
			ms_add_to_env(data, key);
	}
}
