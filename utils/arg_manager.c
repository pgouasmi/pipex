/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arg_manager.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgouasmi <pgouasmi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/09 17:27:29 by pgouasmi          #+#    #+#             */
/*   Updated: 2023/10/13 18:26:16 by pgouasmi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	parse_arg(char **argv, t_arg *args)
{
	args->infile = ft_strdup((const char *)argv[1]);
	if (!args->infile)
		return (1);
	args->fd_infile = open(args->infile, O_RDONLY);
	if (args->fd_infile == -1)
		return (ft_dprintf(2, "%s: %s: no such file or directory\n",
				argv[2], argv[1]), 2);
	args->outfile = ft_strdup((const char *)argv[4]);
	if (!args->outfile)
		return (1);
	args->fd_outfile = open(args->outfile, O_CREAT | O_WRONLY, 0666);
	if (args->fd_outfile == -1)
		return (ft_dprintf(2, "bash: %s: permission denied\n", args->outfile),
			close(args->fd_infile), 3);
	args->commande1 = ft_split((const char *)argv[2], ' ');
	if (!args->commande1)
		return (4);
	args->commande2 = ft_split((const char *)argv[3], ' ');
	if (!args->commande2)
		return (5);
	return (0);
}

static char	*get_zero(char *str)
{
	char	*result;

	result = ft_substr((const char *)str, 5, ft_strlen(str) - 5);
	if (!result)
		return (NULL);
	return (result);
}

static char	*add_ending_slash(char *str)
{
	char	*result;
	size_t	i;

	result = malloc(sizeof(char) * (ft_strlen(str) + 2));
	if (!result)
		return (NULL);
	i = 0;
	while (str[i])
	{
		result[i] = str[i];
		i++;
	}
	result[i] = '/';
	result[i + 1] = '\0';
	return (result);
}

static int	fix_paths(char *str, t_arg *args)
{
	size_t	size;
	size_t	j;

	args->temp = ft_split((const char *)str, ':');
	if (!args->temp)
		return (1);
	size = count_arr_size(args->temp);
	args->paths = malloc(sizeof(char *) * (size + 1));
	if (!args->paths)
		return (2);
	args->paths[size] = NULL;
	args->zero = get_zero(args->temp[0]);
	args->paths[0] = add_ending_slash(args->zero);
	if (!args->paths[0])
		return (free_arr(args->temp), 3);
	free(args->zero);
	j = 0;
	while (++j < size)
	{
		args->paths[j] = add_ending_slash(args->temp[j]);
		if (!args->paths[j])
			return (free_arr(args->temp), 4);
	}
	return (free_arr(args->temp), 0);
}

int	ft_arg_manager(char *envp, char **argv, t_arg *args)
{
	if (fix_paths(envp, args))
		return (1);
	if (parse_arg(argv, args))
		return (2);
	return (0);
}
