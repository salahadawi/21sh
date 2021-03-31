/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_values.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jochumwilen <jochumwilen@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/15 09:26:19 by jwilen            #+#    #+#             */
/*   Updated: 2021/03/31 18:27:06 by jochumwilen      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test.h"

int			return_inv(int ret, int inv)
{
	if (inv % 2)
		return (!ret);
	return (ret);
}

static int	check_unary_values_alfa(char *path, int flag)
{
	if (flag == flag_r)
		return (flag_r_test(path));
	if (flag == flag_s)
		return (flag_s_test(path));
	if (flag == flag_cap_s)
		return (flag_cap_s_test(path));
	if (flag == flag_u)
		return (flag_u_test(path));
	if (flag == flag_w)
		return (flag_w_test(path));
	if (flag == flag_x)
		return (flag_x_test(path));
	if (flag == flag_z)
		return (flag_z_test(path));
	return (0);
}

int			check_unary_values(char *path, int flag)
{
	if (flag == flag_b)
		return (flag_b_test(path));
	if (flag == flag_c)
		return (flag_c_test(path));
	if (flag == flag_d)
		return (flag_d_test(path));
	if (flag == flag_e)
		return (flag_e_test(path));
	if (flag == flag_f)
		return (flag_f_test(path));
	if (flag == flag_g)
		return (flag_g_test(path));
	if (flag == flag_cap_l)
		return (flag_cap_l_test(path));
	if (flag == flag_p)
		return (flag_p_test(path));
	return (check_unary_values_alfa(path, flag));
}

int			check_binary_values(char *r, char *l, int bit_flag, int *res)
{
	if (bit_flag == op_eq)
		return (flag_eq_test(r, l, res));
	else if (bit_flag == op_ne)
		return (flag_ne_test(r, l, res));
	else if (bit_flag == op_ge)
		return (flag_ge_test(r, l, res));
	else if (bit_flag == op_gt)
		return (flag_gt_test(r, l, res));
	else if (bit_flag == op_lt)
		return (flag_lt_test(r, l, res));
	else if (bit_flag == op_le)
		return (flag_le_test(r, l, res));
	else if (bit_flag == op_sym_eq)
		return (flag_sym_eq_test(r, l, res));
	else if (bit_flag == op_sym_noteq)
		return (flag_sym_noteq_test(r, l, res));
	return (2);
}
