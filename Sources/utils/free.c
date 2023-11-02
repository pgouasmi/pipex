/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgouasmi <pgouasmi@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/09 17:27:36 by pgouasmi          #+#    #+#             */
/*   Updated: 2023/07/25 15:11:01 by pgouasmi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	free_arr(char **arr)
{
	size_t	j;

	j = 0;
	if (arr)
	{
		while (arr[j])
		{
			free(arr[j]);
			j++;
		}
		free(arr);
	}
}

void	free_struct(t_arg *args)
{
	if (args->infile)
		free(args->infile);
	if (args->outfile)
		free(args->outfile);
	if (args->commande1)
		free_arr(args->commande1);
	if (args->commande2)
		free_arr(args->commande2);
	if (args->paths)
		free_arr(args->paths);
}
