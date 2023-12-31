/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_base.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chonorat <chonorat@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/08 12:39:24 by pgouasmi          #+#    #+#             */
/*   Updated: 2023/08/17 16:55:00 by chonorat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Includes/libft.h"

void	ft_putnbr_base(long long int n, const char *base, size_t *char_count)
{
	size_t	nbr;
	size_t	base_length;

	base_length = ft_strlen(base);
	if (n < 0)
	{
		ft_putchar_pf('-', char_count);
		nbr = n * -1;
	}
	else
		nbr = n;
	if (nbr < base_length)
		ft_putchar_pf(base[nbr], char_count);
	else
	{
		ft_putnbr_base(nbr / base_length, base, char_count);
		ft_putnbr_base(nbr % base_length, base, char_count);
	}
}
