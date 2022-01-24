/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbattest <lbattest@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/24 10:47:27 by lbattest          #+#    #+#             */
/*   Updated: 2022/01/24 12:18:00 by lbattest         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	error(int i)
{
	if (i == 0)
		perror("pipex");
	else if (i == 1)
		write(2, "pipex: command not found\n", 25);
	else if (i == 2)
		write(2, "pipex: not enough arguments\n", 28);
	else if (i == 3)
		write(2, "pipex: can't create a pipe\n", 27);
	else if (i == 4)
		write(2, "pipex: problem when splitting\n", 30);
	exit(1);
}

static void	loop(t_pipe *pipes, int nbcmd, t_basic basic)
{
	int	pid;

	pid = fork();
	if (pid == -1)
		error(0);
	if (pid == 0)
	{
		if (basic.i == 0 && basic.here_doc == 0)
			in_process(pipes[basic.i], basic, basic.argv[1]);
		else if (basic.i == nbcmd - 1)
			out_process(pipes[basic.i - 1], basic, basic.argv[basic.argc - 1]);
	}
	if (basic.i > 0)
	{
		close(pipes[basic.i - 1].in);
		close(pipes[basic.i - 1].out);
	}
}

int	main(int argc, char **argv, char **envp)
{
	int		nbcmd;
	t_basic	basic;
	t_pipe	*pipes;

	if (argc < 5)
		error(2);
	nbcmd = argc - 3;
	basic.i = -1;
	basic.argc = argc;
	basic.argv = argv;
	basic.envp = envp;
	basic.here_doc = 0;
	pipes = malloc(sizeof(t_pipe) * (nbcmd - 1));
	while (++basic.i < nbcmd)
	{
		printf("%d\n", basic.i);
		if (basic.i < nbcmd - 1 && pipe(&pipes[basic.i].in) == -1)
			error(3);
		loop(pipes, nbcmd, basic);
	}
	free(pipes);
	return (0);
}
