/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgouasmi <pgouasmi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/25 10:52:08 by pgouasmi          #+#    #+#             */
/*   Updated: 2023/10/13 17:09:47 by pgouasmi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <stdlib.h>
# include <unistd.h>
# include <stdarg.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <errno.h>
# include "./includes/libft.h"

typedef struct s_arg
{
	char		*infile;
	int			fd_infile;
	char		*outfile;
	int			fd_outfile;
	char		**commande1;
	char		**commande2;
	char		**paths;
	char		**temp;
	char		*zero;
	int			pipe[2];
}		t_arg;

int			ft_arg_manager(char *envp, char **argv, t_arg *args);
int			parse_arg(char **argv, t_arg *args);
void		free_struct(t_arg *args);
void		free_arr(char **arr);
void		print_arr(char **arr);
size_t		count_arr_size(char **arr);
void		pipex(t_arg *args);

#endif