/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgouasmi <pgouasmi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/25 10:50:22 by pgouasmi          #+#    #+#             */
/*   Updated: 2023/10/13 15:23:50 by pgouasmi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

size_t	count_arr_size(char **arr)
{
	size_t	j;

	j = 0;
	while (arr[j])
		j++;
	return (j);
}

size_t	find_index(char **envp)
{
	size_t	j;

	j = 0;
	while (envp[j])
	{
		if (!ft_strncmp((const char *)envp[j], "PATH=", 5))
			return (j);
		j++;
	}
	return (-1);
}

void	init_args(t_arg *args)
{
	args->infile = NULL;
	args->outfile = NULL;
	args->commande1 = NULL;
	args->commande2 = NULL;
	args->paths = NULL;
	args->temp = NULL;
	args->zero = NULL;
}

void	empty_paths(t_arg *args)
{
	args->paths = malloc(sizeof(char *) * 1);
	if (!args->paths)
		return (free_struct(args), exit(1));
	args->paths[0] = NULL;
}

int	main(int argc, char **argv, char **envp)
{
	t_arg	args;
	int		path_index;

	if (argc != 5)
		return (1);
	init_args(&args);
	path_index = find_index(envp);
	if (path_index == -1)
		parse_arg(argv, &args);
	else
	{
		if (ft_arg_manager(envp[path_index], argv, &args))
			return (free_struct(&args), 2);
	}
	pipex(&args);
	close(args.fd_infile);
	close(args.fd_outfile);
	free_struct(&args);
	return (0);
}
