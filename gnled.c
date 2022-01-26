/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gnled.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbattest <lbattest@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/25 11:04:20 by lbattest          #+#    #+#             */
/*   Updated: 2022/01/26 12:11:23 by lbattest         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	following(t_pipe p, t_basic b, int p_tmp[2])
{
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
	exec(b);
}

static void	here_doc_process(t_pipe p, t_basic b)
{
	int		p_tmp[2];
	char	*tmp;
	char	*final;

	pipe(p_tmp);
	final = NULL;
	tmp = NULL;
	while (1)
	{
		write(1, "pipe heredoc> ", 15);
		tmp = get_next_line(0);
		if (!tmp || ft_strncmp(b.limiter, tmp, ft_strlen(b.limiter)) == 0)
			break ;
		final = ft_strjoin_gnl(final, tmp);
		free(tmp);
	}
	write(p_tmp[1], final, ft_strlen(final));
	if (final)
		free(final);
	if (tmp)
		free(tmp);
	free(b.limiter);
	b.i++;
	following(p, b, p_tmp);
}

void	call_me(t_pipe p, t_basic basic)
{
	int		pid;

	pid = fork();
	if (pid == 0)
	{
		basic.limiter = ft_strjoin(basic.argv[2], "\n");
		if (!basic.limiter)
			error(5);
		here_doc_process(p, basic);
	}
	else
		waitpid(pid, NULL, 0);
}
