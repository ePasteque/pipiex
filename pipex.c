/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbattest <lbattest@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/14 18:30:46 by lbattest          #+#    #+#             */
/*   Updated: 2021/12/22 16:43:07 by lbattest         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	error(int i)
{
	if (i == 1)
		write(1, "There is not enough arguments", 29);
	else if (i == 2)
		write(1, "Bad permission", 14);
	else if (i == 3)
		write(1, "Can't open pipe", 15);
	else if (i == 4)
		write(1, "Problem with a malloc", 21);
	else if (i == 5)
		write(1, "Problem when opening the file", 29);
	exit(1);
}

static void	*free_all(char **str)
{
	int	i;

	i = 0;
	while (str[i])
		free(str[i++]);
	free(str);
	return (0);
}

char	*get_path(char **envp, char *cmd)
{
	char	*path;
	char	**tmp;
	char	*test;
	int		i;

	path = NULL;
	i = 0;
	while (envp[i])
	{
		if (ft_memcmp(envp[i], "PATH=", 5) == 0)
		{
			path = &envp[i][5];
			break ;
		}
		i++;
	}
	if (!path)
		return (NULL);
	i = 0;
	tmp = ft_split(path, ':');
	while (access(path, X_OK | F_OK) == -1 && tmp[i])
	{
		path = ft_strjoin(tmp[i], "/");
		path = ft_strjoin(path, cmd);
		i++;
	}
	free_all(tmp);
	return (path);
}

static int	split_ine(char **str, char **argv, int i, char c)
{
	int	j;

	j = 0;
	while (*argv[i] != c && *argv[i])
		*str[j++] = *argv[i++];
	return (i);
}

/*
	argv[1] is the "read" file
	then at least 2 cmd command 
	and the last argv is the return file
*/

int	main(int argc, char **argv, char **envp)
{
	int		i;
	char	*path;
	int		fdd[2];
	int		id;
	char	**cmd;
	int		fd;

	i = 1;
	if (argc < 5)
		error(1);
	// if (access(argv[i], R_OK) == -1)
	// 	error(2);
	fd = open(argv[1], O_RDONLY);
	if (fd == -1)
		error(5);
	dup2(fd, 0); // comme la mais l'inverse
	if (pipe(fdd) == -1)
		error(3);
	id = fork();
	if (id == 0) // cat
	{
		close(fdd[0]);
		dup2(fdd[1], 1);
		cmd = ft_split(argv[2], ' ');
		if (!cmd)
			error(4);
		path = get_path(envp, cmd[0]);
		free(cmd[0]);
		cmd[0] = path;
		if (execve(path, cmd, envp) < 0)
			error(5);
	}
	else // wc
	{
		close(fdd[1]);
		dup2(fdd[0], 0);
		cmd = ft_split(argv[3], ' ');
		if (!cmd)
			error(4);
		path = get_path(envp, cmd[0]);
		free(cmd[0]);
		cmd[0] = path;
		wait(NULL);
		if (execve(path, cmd, envp) < 0)
			error(5);
		// rediriger la sortie standare(1) vers le fichier de sortie en utilisant open() pour ouvrir et cree le fichier puis dub2()
	}
	close(fd);
	free_all(cmd);
	free(path);
	return (0);
}
