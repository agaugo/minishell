//
// Created by Hugo Flohil de Sousa on 25/08/2023.
//

//EVERYTHING HERE BELONGS TO PIPEX

//lexer

void	free_all(char **exec_args)
{
	int	i;

	i = 0;
	while (exec_args[i] != NULL)
		free(exec_args[i]);
	free(exec_args);
}

int	count_args(char *cmd_buffer)
{
	int	i;
	int	c;

	i = 0;
	c = 0;
	while (cmd_buffer[i] != '\0')
	{
		if (cmd_buffer[i] == ' ')
			c++;
		i++;
	}
	if (c == 0)
		c++;
	return (c);
}

char	*get_root_dir(char *arg1)
{
	char	*dirs[4];
	char	*return_dir;
	int		i;

	dirs[0] = "/bin/";
	dirs[1] = "/usr/bin/";
	dirs[2] = "/usr/local/bin/";
	dirs[3] = NULL;
	i = 0;
	while (dirs[i] != NULL)
	{
		return_dir = ft_strjoin(dirs[i], arg1);
		if (access(return_dir, F_OK) != -1)
			return (return_dir);
		free(return_dir);
		i++;
	}
	return (NULL);
}

char	**get_args(char *cmd_buffer, int count, int i)
{
	char	**full_exec_args;
	char	**partial_exec_args;

	full_exec_args = malloc((sizeof(char *) * count + 1));
	if (!full_exec_args)
		return (NULL);
	if (count != 0)
	{
		partial_exec_args = ft_split(cmd_buffer, ' ');
		while (partial_exec_args[i] != NULL)
		{
			if (i == 0)
				full_exec_args[i] = get_root_dir(partial_exec_args[i]);
			else
				full_exec_args[i] = partial_exec_args[i];
			i++;
		}
		full_exec_args[i] = NULL;
	}
	else
	{
		full_exec_args[0] = get_root_dir(cmd_buffer);
		full_exec_args[1] = NULL;
	}
	return (full_exec_args);
}

//executes:

int	child(int *fd_pipe, int fd_infile, char *cmd_buffer)
{
	char	**exec_args;

	exec_args = get_args(cmd_buffer, count_args(cmd_buffer), 0);
	printf("child process (infile) %s %s\n", exec_args[0], exec_args[1]);
	close(fd_pipe[0]);
	dup2(fd_infile, 0);
	dup2(fd_pipe[1], 1);
	if (execve(exec_args[0], exec_args, NULL) == -1)
	{
		perror(exec_args[0]);
		exit(1);
	}
	return (0);
}

int	parent(int *fd_pipe, int fd_outfile, char *cmd_buffer)
{
	char	**exec_args;

	exec_args = get_args(cmd_buffer, count_args(cmd_buffer), 0);
	printf("parent process (outfile) %s %s\n", exec_args[0], exec_args[1]);
	close(fd_pipe[1]);
	dup2(fd_pipe[0], 0);
	dup2(fd_outfile, 1);
	if (execve(exec_args[0], exec_args, NULL) == -1)
	{
		perror(exec_args[0]);
		exit(1);
	}
	return (0);
}

int	main(int argc, char *argv[])
{
	int	fd_pipe[2];
	int	process_id;
	int	fd_infile;
	int	fd_outfile;

	if (argc != 5)
		return (0);
	fd_infile = open(argv[1], O_RDONLY);
    if (fd_infile == -1)
        return (0);
	fd_outfile = open(argv[4], O_WRONLY | O_CREAT, 0644);
	if (pipe(fd_pipe) < 0)
		return (1);
	process_id = fork();
	if (process_id == 0)
		child(fd_pipe, fd_infile, argv[2]);
	else
	{
		wait(NULL);
		parent(fd_pipe, fd_outfile, argv[3]);
	}
	return (0);
}
