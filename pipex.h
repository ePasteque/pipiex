/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbattest <lbattest@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/15 10:01:54 by lbattest          #+#    #+#             */
/*   Updated: 2022/01/25 17:36:08 by lbattest         ###   ########.fr       */
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
	int			here_doc;
	int			argc;
	int			append;
	char		*limiter;
	char		**argv;
	char		**envp;
}				t_basic;

void	error(int i);
void	in_process(t_pipe p, t_basic basic, char *infile);
void	sub_process(t_pipe pin, t_pipe pout, t_basic basic);
void	out_process(t_pipe p, t_basic basic, char *outfile);
char	*get_path(char **envp, char *cmd);
void	*free_all(char **str);
void	call_me(t_pipe p, t_basic basic);
void	exec(t_basic basic);

#endif