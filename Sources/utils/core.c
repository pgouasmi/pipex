/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   core.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgouasmi <pgouasmi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/10 10:50:57 by pgouasmi          #+#    #+#             */
/*   Updated: 2023/11/02 18:47:18 by pgouasmi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	fd_handler_exec(t_arg *args)
{
	if (access(args->outfile, F_OK))
		return (0);
	if (access(args->outfile, W_OK))
		return (ft_dprintf(2, "bash: %s: Permission denied\n",
				args->outfile), 1);
	else if (!access(args->outfile, ENOTDIR))
		return (ft_dprintf(2, "bash: %s: Is a directory\n", args->outfile), 1);
	return (0);
}

void	close_std_fd(void)
{
	close(0);
	close(1);
	close(2);
}

int	first_cmd(t_arg *args)
{
	size_t	j;
	char	*temp;

	j = -1;
	if (args->fd_infile == 0)
		return (close(args->pipe[0]), close(args->pipe[1]),
			close(args->fd_outfile), close_std_fd(), 1);
	if (dup2(args->fd_infile, STDIN_FILENO) == -1)
		return (free_struct(args), exit(2), 1);
	if (dup2(args->pipe[1], STDOUT_FILENO) == -1)
		return (free_struct(args), exit(3), 1);
	close(args->pipe[0]);
	close(args->fd_infile);
	while (args->paths[++j])
	{
		temp = ft_strjoin(args->paths[j], args->commande1[0]);
		if (!temp)
			return (free_struct(args), exit(4), 1);
		if ((execve(temp, args->commande1, NULL)) == -1)
			free(temp);
	}
	return (ft_dprintf(2, "bash: %s: command not found\n", args->commande1[0]),
		free_struct(args), close(args->pipe[1]), close(args->fd_outfile),
		close_std_fd(), exit(5), 1);
}

int	second_cmd(t_arg *args)
{
	size_t	j;
	char	*temp;

	wait(NULL);
	if (args->fd_outfile == 1)
		return (close(args->pipe[0]), fd_handler_exec(args), close_std_fd(), 1);
	if (dup2(args->pipe[0], STDIN_FILENO) == -1)
		return (free_struct(args), exit(2), 1);
	if (dup2(args->fd_outfile, STDOUT_FILENO) == -1)
		return (free_struct(args), exit(3), 1);
	close(args->pipe[1]);
	close(args->fd_outfile);
	j = -1;
	while (args->paths[++j])
	{
		temp = ft_strjoin(args->paths[j], args->commande2[0]);
		if (!temp)
			return (free_struct(args), exit(6), 1);
		if ((execve(temp, args->commande2, NULL)) == -1)
			free(temp);
	}
	return (ft_dprintf(2, "bash: %s: command not found\n", args->commande2[0]),
		free_struct(args), close(args->pipe[0]), close(args->fd_infile),
		close(0), close(1), close(2), exit(7), 1);
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
	if (args->fd_infile != 0 && args->fd_infile != -1)
		close(args->fd_infile);
	if (args->fd_outfile != 1 && args->fd_outfile != -1)
		close(args->fd_outfile);
	close_std_fd();
	return ;
}
