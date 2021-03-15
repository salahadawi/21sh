/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flag_binary_sym.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwilen <jwilen@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/15 09:18:58 by jwilen            #+#    #+#             */
/*   Updated: 2021/03/15 09:24:06 by jwilen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test.h"

int		flag_sym_eq_test(char *left, char *right, int *result)
{
	if (ft_strequ(left, right))
		*result = 0;
	else
		*result = 1;
	return (0);
}

int		flag_sym_noteq_test(char *left, char *right, int *result)
{
	if (!ft_strequ(left, right))
		*result = 0;
	else
		*result = 1;
	return (0);
}
