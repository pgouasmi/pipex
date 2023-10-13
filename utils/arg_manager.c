/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arg_manager.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgouasmi <pgouasmi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/09 17:27:29 by pgouasmi          #+#    #+#             */
/*   Updated: 2023/10/13 19:53:30 by pgouasmi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	fd_issue_handler(t_arg *args)
{
	int	issue;

	issue = 0;
	if (args->fd_infile == -1)
	{
		issue++;
		ft_dprintf(2, "bash: %s: no such file or directory\n",
			args->infile);
		if (args->fd_outfile != -1)
			close(args->fd_outfile);
	}
	if (args->fd_outfile == -1)
	{
		issue++;
		ft_dprintf(2, "bash: %s: permission denied\n", args->outfile);
		if (args->fd_infile != -1)
			close(args->fd_infile);
	}
	return (issue);
}

int	parse_arg(char **argv, t_arg *args)
{
	args->infile = ft_strdup((const char *)argv[1]);
	if (!args->infile)
		return (1);
	args->fd_infile = open(args->infile, O_RDONLY);
	args->outfile = ft_strdup((const char *)argv[4]);
	if (!args->outfile)
		return (2);
	args->fd_outfile = open(args->outfile, O_CREAT | O_WRONLY, 0666);
	if (fd_issue_handler(args))
		return (free_struct(args),
			close(1), close(2), close(0), exit(3), 3);
	args->commande1 = ft_split((const char *)argv[2], ' ');
	if (!args->commande1)
		return (4);
	args->commande2 = ft_split((const char *)argv[3], ' ');
	if (!args->commande2)
		return (5);
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
