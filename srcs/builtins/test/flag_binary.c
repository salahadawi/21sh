/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flag_binary.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwilen <jwilen@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/15 09:10:56 by jwilen            #+#    #+#             */
/*   Updated: 2021/03/15 12:06:23 by jwilen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test.h"

int			flag_eq_test(char *l, char *r, int *res)
{
	long long	vl;
	long long	vr;

	if (check_longlong(l, &vl))
		return (2);
	if (check_longlong(r, &vr))
		return (2);
	if (vl == vr)
		*res = 0;
	else
		*res = 1;
	return (0);
}

int			flag_ne_test(char *r, char *l, int *res)
{
	long long	vl;
	long long	vr;

	if (check_longlong(l, &vl))
		return (2);
	if (check_longlong(r, &vr))
		return (2);
	if (vl != vr)
		*res = 0;
	else
		*res = 1;
	return (0);
}

int			flag_ge_test(char *r, char *l, int *res)
{
	long long	vl;
	long long	vr;

	if (check_longlong(l, &vl))
		return (2);
	if (check_longlong(r, &vr))
		return (2);
	if (vl <= vr)
		*res = 0;
	else
		*res = 1;
	return (0);
}

int			flag_lt_test(char *r, char *l, int *res)
{
	long long	vl;
	long long	vr;

	if (check_longlong(l, &vl))
		return (2);
	if (check_longlong(r, &vr))
		return (2);
	if (vl > vr)
		*res = 0;
	else
		*res = 1;
	return (0);
}

int			flag_le_test(char *r, char *l, int *res)
{
	long long	vl;
	long long	vr;

	if (check_longlong(l, &vl))
		return (2);
	if (check_longlong(r, &vr))
		return (2);
	if (vl >= vr)
		*res = 0;
	else
		*res = 1;
	return (0);
}
