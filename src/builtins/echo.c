/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   echo.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: trstn4 <trstn4@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/23 00:11:40 by trstn4        #+#    #+#                 */
/*   Updated: 2023/12/13 15:47:48 by trstn4        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void open_error(t_data *data)
{
	perror("open");
	data->last_exit_code = 1;
	return ;
}

t_token_t	*set_token(t_token_t *token)
{
	if (token->next)
		token = token->next->next;
	else
		token = NULL;
	return (token);
}
void	restore_and_close(int flag_n, int stdout_backup, t_data *data)
{
	if (!flag_n)
		printf("\n");
	dup2(stdout_backup, STDOUT_FILENO);
	close(stdout_backup);
	data->last_exit_code = 0;
}

void	dup_and_close(int fd)
{
	dup2(fd, STDOUT_FILENO);
	close(fd);
}
void	should_print_space_func(int *should_print_space, t_token_t *token)
{
	if (*should_print_space)
		printf(" ");
	printf("%s", token->value);
	*should_print_space = 1;
}
void	fill_flag(t_token_t *token, int *flags)
{
	if (token->type == T_APPEND_OUT)
		*flags = O_WRONLY | O_CREAT | O_APPEND;
	else
		*flags = O_WRONLY | O_CREAT | O_TRUNC;
}
t_token_t *if_body1(t_token_t *token, int *flags)
{
	fill_flag(token, flags);
	token = token->next;
	return (token);
}

t_token_t *if_body2(int *fd, t_token_t *token, int *flags, t_data *data)
{
	*fd = open(token->value, *flags, 0666);
	if (fd < 0)
	{
		open_error(data);
		return (token);
	}
	dup_and_close(*fd);
	token = token->next;
	return (token);
}
t_token_t	*type_append_or_out(t_token_t *token, int *flags, t_data *data, int *fd)
{
	if_body1(token, flags);
	if (token && token->value) 
		token = if_body2(fd, token, flags, data);
	return (token);
}
t_token_t	*big_mama(t_token_t *token, int *flags, t_data *data, int *fd, int *should_print_space)
{
	if (token->type == T_REDIRECT_OUT || token->type == T_APPEND_OUT)
		token = type_append_or_out(token, flags, data, fd);
	else if (token->type == T_REDIRECT_IN)
		token = set_token(token);
	else if (token && token->type == T_WORD)
		should_print_space_func(should_print_space, token);
	return (token);
}

t_token_t	*assign_flag_n(t_token_t *token, int *flag_n)
{
	*flag_n = 1;
	token = token->next;
	return (token);
}
void ms_echo_command(t_data *data, t_token_t *token)
{
    int flag_n = 0;
    int first_word = 1;
    int stdout_backup = dup(STDOUT_FILENO);
    int should_print_space = 0;
    int flags;
    int fd;

    token = token->next;
    while (token) 
	{
        if (token->type == T_PIPE)
            break;
        if (first_word) 
		{
            if (ft_strcmp(token->value, "-n") == 0) 
			{
				token = (assign_flag_n(token, &flag_n));
                continue;
            }
            first_word = 0;
        }
		token = big_mama(token, &flags, data, &fd, &should_print_space);
        token = token->next;
    }
    restore_and_close(flag_n, stdout_backup, data);
}


//OLD VERSION


// void ms_echo_command(t_data *data, t_token_t *token)
// {
// 	int flag_n;
// 	int first_word;
// 	int stdout_backup;
// 	int should_print_space;
// 	int flags;
// 	int fd;

// 	flag_n = 0;
// 	first_word = 1;
// 	should_print_space = 0;	
// 	stdout_backup = dup(STDOUT_FILENO);
// 	token = token->next;
// 	while (token)
// 	{
// 		if (token->type == T_PIPE)
// 			break ;
// 		if (first_word && ft_strcmp(token->value, "-n") == 0)
// 		{
// 			flag_n = 1;
// 			token = token->next;
// 			continue ;
// 		}
// 		first_word = 0;
// 		if (token->type == T_REDIRECT_OUT || token->type == T_APPEND_OUT)
// 		{
// 			if_body1(token, &flags);
// 			if (token && token->value)
// 			{
// 				if_body2(&fd, token, flags, data);
// 				continue ;
// 			}
// 		}
// 		if (token->type == T_REDIRECT_IN)
// 		{
// 			set_token(token);
// 			continue ;
// 		}
// 		if (token && token->type == T_WORD)
// 			should_print_space_func(&should_print_space, token);
// 		token = token->next;
// 	}
// 	restore_and_close(flag_n, stdout_backup, data);
// }

