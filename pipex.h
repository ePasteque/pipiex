/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbattest <lbattest@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/15 10:01:54 by lbattest          #+#    #+#             */
/*   Updated: 2022/01/13 18:33:17 by lbattest         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <stdbool.h>
# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <stdio.h>
# include "libft/libft.h"

typedef struct s_pipe
{
	int			in;
	int			out;
}				t_pipe;

typedef struct s_basic
{
	int			i;
	int			argc;
	char		**argv;
	char		**envp;
}				t_basic;

void	error(int i);
int		ft_strcmp(const char *s1, const char *s2);
void	in_process(t_pipe p, t_basic basic, char *infile);
void	sub_process(t_pipe pin, t_pipe pout, t_basic basic);
void	out_process(t_pipe p, t_basic basic, char *outfile);
char	*get_path(char **envp, char *cmd);
void	*free_all(char **str);

#endif