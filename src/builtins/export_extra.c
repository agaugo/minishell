/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   export_extra.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: trstn4 <trstn4@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/23 17:46:14 by trstn4        #+#    #+#                 */
/*   Updated: 2023/12/13 20:28:50 by trstn4        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static char	*ms_assignment_set_attr1(char *new_assignment, char *value,
	char *key)
{
	size_t	total_len;
	int		i;
	int		j;

	total_len = ft_strlen(key) + ft_strlen(value) + 4;
	new_assignment = (char *)allocate_memory(total_len);
	i = 0;
	while (key[i] != '\0')
	{
		new_assignment[i] = key[i];
		i++;
	}
	new_assignment[i++] = '=';
	new_assignment[i++] = '\"';
	j = 0;
	while (value[j] != '\0')
	{
		new_assignment[i + j] = value[j];
		j++;
	}
	new_assignment[i + j++] = '\"';
	new_assignment[i + j] = '\0';
	return (new_assignment);
}

static char	*ms_assignment_set_attr2(char *new_assignment, char *value,
	char *key)
{
	size_t	total_len;
	int		i;
	int		j;

	total_len = ft_strlen(key) + ft_strlen(value) + 2;
	new_assignment = (char *)allocate_memory(total_len);
	i = 0;
	while (key[i] != '\0')
	{
		new_assignment[i] = key[i];
		i++;
	}
	new_assignment[i++] = '=';
	j = 0;
	while (value[j] != '\0')
	{
		new_assignment[i + j] = value[j];
		j++;
	}
	new_assignment[i + j] = '\0';
	return (new_assignment);
}

char	*create_assignment(char *key, char *value)
{
	char	*new_assignment;

	new_assignment = NULL;
	if (ft_strchr(value, ' ') || ft_strchr(value, '\t')
		|| ft_strchr(value, '\"') || ft_strchr(value, '\''))
		new_assignment = ms_assignment_set_attr1(new_assignment, value, key);
	else
		new_assignment = ms_assignment_set_attr2(new_assignment, value, key);
	return (new_assignment);
}
