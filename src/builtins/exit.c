/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   exit.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: trstn4 <trstn4@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/08/25 10:37:37 by trstn4        #+#    #+#                 */
/*   Updated: 2023/12/11 18:03:48 by trstn4        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ms_str_isdigit(const char *str)
{
	if (str == NULL)
		return (0);
	if (*str == '-' || *str == '+')
		str++;
	while (*str != '\0')
	{
		if (*str < '0' || *str > '9')
			return (0);
		else
			str++;
	}
	return (1);
}

static char	*ms_process_quotes(char *temp_value, token_t *token)
{
	char	*inner_value;

	if ((*temp_value == '-' || *temp_value == '+') && temp_value[1] == '\"'
		&& temp_value[ft_strlen(temp_value) - 1] == '\"')
	{
		inner_value = ft_strndup(temp_value + 2, ft_strlen(temp_value) - 3);
		temp_value = (char *)allocate_memory(ft_strlen(inner_value) + 2);
		temp_value[0] = token->value[0];
		ft_strcpy(temp_value + 1, inner_value);
		// debug(temp_value); //for testing
		free_memory(inner_value);
	}
	if (temp_value[0] == '\"'
		&& temp_value[ft_strlen(temp_value) - 1] == '\"')
	{
		inner_value = ft_strndup(temp_value + 1, ft_strlen(temp_value) - 2);
		if (temp_value != token->value)
			free_memory(temp_value);
		temp_value = inner_value;
	}
	return (temp_value);
}

static void	ms_check_args_and_exit(data_t *data, token_t *token, char *temp_value)
{
	int	exit_code;

	if (ms_str_isdigit(temp_value) == 0)
	{
		fprintf(stderr, "exit: %s: numeric argument required\n",
			token->value);
		if (temp_value != token->value)
			free_memory(temp_value);
		exit(255);
	}
	exit_code = ft_atoi(temp_value);
	if (temp_value != token->value)
		free_memory(temp_value);
	printf("exit\n");
	wipe_data_struct(data);
	exit(exit_code % 256);

}

void	ms_exit_shell(data_t *data, token_t *token)
{
	char	*temp_value;

	if (!token)
	{
		printf("exit\n");
		wipe_data_struct(data);
		exit(0);
	}
	if (token->type == T_WORD && token->next
		&& token->next->type == T_WORD)
	{
		fprintf(stderr, "exit: too many arguments\n");
		data->last_exit_code = 1;
		return ;
	}
	temp_value = token->value;
	temp_value = ms_process_quotes(temp_value, token);
	ms_check_args_and_exit(data, token, temp_value);
}
