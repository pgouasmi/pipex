/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_paths.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgouasmi <pgouasmi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/13 19:44:15 by pgouasmi          #+#    #+#             */
/*   Updated: 2023/10/13 19:44:57 by pgouasmi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

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

int	fix_paths(char *str, t_arg *args)
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
