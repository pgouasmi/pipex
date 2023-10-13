/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   core.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgouasmi <pgouasmi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/10 10:50:57 by pgouasmi          #+#    #+#             */
/*   Updated: 2023/10/13 18:36:48 by pgouasmi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	first_cmd(t_arg *args)
{
	size_t	j;
	char	*temp;

	j = -1;
	if (dup2(args->fd_infile, STDIN_FILENO) == -1)
		return (free_struct(args), exit(2));
	if (dup2(args->pipe[1], STDOUT_FILENO) == -1)
		return (free_struct(args), exit(3));
	close(args->pipe[0]);
	close(args->fd_infile);
	while (args->paths[++j])
	{
		temp = ft_strjoin(args->paths[j], args->commande1[0]);
		if (!temp)
			return (free_struct(args), exit(4));
		if ((execve(temp, args->commande1, NULL)) == -1)
			free(temp);
	}
	return (ft_dprintf(2, "bash: %s: command not found\n", args->commande1[0]),
		free_struct(args), close(args->pipe[1]), close(args->fd_outfile),
		close(0), close(1), close(2), exit(5));
}

void	second_cmd(t_arg *args)
{
	size_t	j;
	char	*temp;

	wait(NULL);
	dup2(args->pipe[0], STDIN_FILENO);
	dup2(args->fd_outfile, STDOUT_FILENO);
	close(args->pipe[1]);
	close(args->fd_outfile);
	j = -1;
	while (args->paths[++j])
	{
		temp = ft_strjoin(args->paths[j], args->commande2[0]);
		if (!temp)
			return (free_struct(args), exit(6));
		if ((execve(temp, args->commande2, NULL)) == -1)
			free(temp);
	}
	return (ft_dprintf(2, "bash: %s: command not found\n", args->commande2[0]),
		free_struct(args), close(args->pipe[0]), close(args->fd_infile),
		close(0), close(1), close(2), exit(7));
}

void	pipex(t_arg *args)
{
	pid_t	child1;
	pid_t	child2;

	pipe(args->pipe);
	child1 = fork();
	if (child1 == -1)
		return (free_struct(args), exit(1));
	if (child1 == 0)
		first_cmd(args);
	child2 = fork();
	if (child2 == -1)
		return (free_struct(args), exit(3));
	if (child2 == 0)
		second_cmd(args);
	close(args->pipe[0]);
	close(args->pipe[1]);
	waitpid(child1, NULL, 0);
	waitpid(child2, NULL, 0);
	close(args->fd_infile);
	close(args->fd_outfile);
	close(0);
	close(1);
	close(2);
	return ;
}
