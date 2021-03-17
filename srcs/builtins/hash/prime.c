/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prime.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwilen <jwilen@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/16 10:20:45 by jwilen            #+#    #+#             */
/*   Updated: 2021/03/16 10:24:06 by jwilen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hash.h"

static int		is_prime(int nb)
{
	int	i;

	if (nb < 2)
		return (0);
	if (nb <= 3)
		return (1);
	if ((nb % 2 == 0) || (nb % 3 == 0))
		return (0);
	i = 5;
	while (i * i < (int)nb)
	{
		if ((nb % i == 0) || (nb % (i + 2) == 0))
			return (0);
		i += 6;
	}
	return (1);
}

int				get_new_prime(int nb)
{
	while (++nb && nb <= INT_MAX)
	{
		if (is_prime(nb))
			return (nb);
	}
	return (0);
}
