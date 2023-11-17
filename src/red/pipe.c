/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hflohil- <hflohil-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/23 16:37:59 by hflohil-          #+#    #+#             */
/*   Updated: 2023/08/23 15:18:23 by hflohil-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "pipex.h"
#include <fcntl.h>
#include <stdio.h>
#include <sys/wait.h>
#include <unistd.h>

void	handle_error(int exit_code, const char *message)
{
    perror(message);
    exit(exit_code);
}

void	child(int *fd_pipe, char **argv, char **envp)
{
    int	infile;

    infile = open(argv[1], O_RDONLY, 0666);
    if (infile == -1)
        handle_error(1, "Unable to open input file");
    if (dup2(fd_pipe[1], 1) == -1)
        handle_error(1, "Error redirecting output to pipe");
    if (dup2(infile, 0) == -1)
        handle_error(1, "Error redirecting input from file");
    close(fd_pipe[0]);
    execute(argv[2], envp);
}

void	parent(int *fd_pipe, char **argv, char **envp)
{
    int	outfile;

    outfile = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC, 0666);
    if (outfile == -1)
        handle_error(2, "Unable to open output file");
    if (dup2(fd_pipe[0], 0) == -1)
        handle_error(2, "Error redirecting input from pipe");
    if (dup2(outfile, 1) == -1)
        handle_error(2, "Error redirecting output to file");
    close(fd_pipe[1]);
    execute(argv[3], envp);
}

int	pipe(int argc, char *argv[], char *envp[])
{
    int	fd_pipe[2];
    int	process_id;

    if (argc != 5)
        exit(2);
    if (pipe(fd_pipe) == -1)
        handle_error(1, "Pipe creation error");
    process_id = fork();
    if (process_id == -1)
        handle_error(1, "Fork error");
    if (process_id == 0)
        child(fd_pipe, argv, envp);
    parent(fd_pipe, argv, envp);
    return (0);
}

void ms_check_pipe(data_t *data) {
    token_t *token;

    token = data->tokens->next;
    while (token != NULL)
    {
        if (token->type == T_PIPE)
        {
            ms_pipe(data);
            data->redirect = 1;
            return ;
        }
        token = token->next;
    }
    return ;

}
