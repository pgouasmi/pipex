/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arg_manager.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgouasmi <pgouasmi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/09 17:27:29 by pgouasmi          #+#    #+#             */
/*   Updated: 2023/11/02 18:48:57 by pgouasmi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	fd_handler(t_arg *args, int type)
{
	if (type == 0)
	{
		if (access(args->infile, F_OK))
			return (ft_dprintf(2, "bash: %s: No such file or directory\n",
					args->infile), 1);
		else if (access(args->infile, R_OK))
			return (ft_dprintf(2, "bash: %s: Permission denied\n",
					args->infile), 1);
		else if (!access(args->infile, ENOTDIR))
			return (ft_dprintf(2, "%s: -: Is a directory\n",
					args->commande1[0]), 1);
	}
	else
	{
		if (access(args->outfile, F_OK))
			return (0);
		if (access(args->outfile, W_OK))
			return (1);
		else if (!access(args->outfile, ENOTDIR))
			return (1);
	}
	return (0);
}

int	parse_arg(char **argv, t_arg *args)
{
	args->infile = ft_strdup((const char *)argv[1]);
	if (!args->infile)
		return (1);
	args->commande1 = ft_split((const char *)argv[2], ' ');
	if (!args->commande1)
		return (3);
	if (fd_handler(args, 0))
		args->fd_infile = 0;
	else
		args->fd_infile = open(args->infile, O_RDONLY);
	args->outfile = ft_strdup((const char *)argv[4]);
	if (!args->outfile)
		return (2);
	args->commande2 = ft_split((const char *)argv[3], ' ');
	if (!args->commande2)
		return (4);
	if (fd_handler(args, 1))
		args->fd_outfile = 1;
	else
		args->fd_outfile = open(args->outfile,
				O_CREAT | O_WRONLY | O_TRUNC, 0666);
	return (0);
}

int	ft_arg_manager(char *envp, char **argv, t_arg *args)
{
	if (fix_paths(envp, args))
		return (1);
	if (parse_arg(argv, args))
		return (2);
	return (0);
}
