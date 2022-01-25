/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbattest <lbattest@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/28 14:01:03 by lbattest          #+#    #+#             */
/*   Updated: 2022/01/25 18:11:19 by lbattest         ###   ########.fr       */
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
	else if (i == 5)
		write(2, "pipex: error malloc with here_doc\n", 34);
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
		else if (basic.i != 0)
			sub_process(pipes[basic.i - 1], pipes[basic.i], basic);
	}
	if (basic.i > 0)
	{
		close(pipes[basic.i - 1].in);
		close(pipes[basic.i - 1].out);
	}
}

int	init(int argc, char **argv, char **envp, t_basic *basic)
{
	basic->i = -1;
	basic->argc = argc;
	basic->argv = argv;
	basic->envp = envp;
	basic->here_doc = 0;
	return (argc - 3);
}

int	main(int argc, char **argv, char **envp)
{
	int		nbcmd;
	t_basic	basic;
	t_pipe	*pipes;

	if (argc < 5)
		error(2);
	nbcmd = init(argc, argv, envp, &basic);
	pipes = malloc(sizeof(t_pipe) * (nbcmd - 1));
	if (ft_strncmp(argv[1], "here_doc", 8) == 0)
	{
		if (pipe(&pipes[++basic.i].in) == -1)
			error(3);
		call_me(pipes[basic.i], basic);
		basic.here_doc++;
	}
	while (++basic.i < nbcmd)
	{
		if (basic.i < nbcmd - 1 && pipe(&pipes[basic.i].in) == -1)
			error(3);
		loop(pipes, nbcmd, basic);
	}
	while (wait(NULL) != -1)
		;
	free(pipes);
	return (0);
}
