/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbattest <lbattest@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/13 16:24:15 by lbattest          #+#    #+#             */
/*   Updated: 2022/01/18 19:33:15 by lbattest         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	exec(t_basic basic)
{
	char	**cmd;
	char	*tmp;

	cmd = ft_split(basic.argv[basic.i + 2], ' ');
	if (!cmd)
		error(4);
	tmp = get_path(basic.envp, cmd[0]);
	if (tmp == NULL)
		error(1);
	free(cmd[0]);
	cmd[0] = tmp;
	if (execve(cmd[0], cmd, basic.envp) < 0)
	{
		free_all(cmd);
		error(0);
	}
}

void	here_doc_process(t_pipe p, t_basic basic)
{
	int		p_tmp[2];
	char	*tmp;
	char	*final;

	pipe(p_tmp);
	final = NULL;
	tmp = get_next_line(0); // je pense que c'est un probleme avec l'implementation de gnl dans libft
	while (tmp && ft_strncmp(basic.argv[2], tmp, ft_strlen(basic.argv[2])) != 0)
	{
		ft_strlcat(final, tmp, ft_strlen(final) + ft_strlen(tmp) + 1);
		tmp = get_next_line(0);
	}
	ft_strlcat(final, tmp, ft_strlen(final) + ft_strlen(tmp) + 1);
	write(p_tmp[0], final, ft_strlen(final));
	basic.i++;
	if (dup2(p_tmp[0], 0) < 0)
		error(0);
	if (close(p_tmp[0]))
		error(0);
	if (close(p_tmp[1]))
		error(0);
	if (dup2(p.out, 1) < 0)
		error(0);
	if (close(p.in) < 0)
		error(0);
	if (close(p.out) < 0)
		error(0);
	exec(basic);
}

void	in_process(t_pipe p, t_basic basic, char *infile)
{
	int		fd;

	fd = open(infile, O_RDONLY);
	if (fd == -1)
		error(0);
	if (dup2(fd, 0) < 0)
		error(0);
	if (dup2(p.out, 1) < 0)
		error(0);
	if (close(fd) < 0)
		error(0);
	if (close(p.in) < 0)
		error(0);
	if (close(p.out) < 0)
		error(0);
	exec(basic);
}

void	sub_process(t_pipe pin, t_pipe pout, t_basic basic)
{
	if (dup2(pin.in, 0) < 0)
		error(0);
	if (dup2(pout.out, 1) < 0)
		error(0);
	if (close(pin.in) < 0)
		error(0);
	if (close(pin.out) < 0)
		error(0);
	if (close(pout.in) < 0)
		error(0);
	if (close(pout.out) < 0)
		error(0);
	exec(basic);
}

void	out_process(t_pipe p, t_basic basic, char *outfile)
{
	int	fd;

	fd = open(outfile, O_CREAT | O_TRUNC | O_WRONLY, 0644);
	if (fd == -1)
		error(0);
	if (dup2(fd, 1) < 0)
		error(0);
	if (dup2(p.in, 0) < 0)
		error(0);
	if (close(fd) < 0)
		error(0);
	if (close(p.in) < 0)
		error(0);
	if (close(p.out) < 0)
		error(0);
	exec(basic);
}
