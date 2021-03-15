/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwilen <jwilen@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/11 22:06:23 by jwilen            #+#    #+#             */
/*   Updated: 2021/03/15 10:23:34 by jwilen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TEST_H
# define TEST_H

# include "sh.h"

typedef enum	e_test {
	flag_b = 1,
	flag_c,
    flag_d,
    flag_e,
    flag_f,
    flag_g,
    flag_cap_l,
    flag_p,
    flag_r,
    flag_s,
    flag_cap_s,
    flag_u,
    flag_w,
    flag_x,
    flag_z,
    op_eq,
	op_ne,
	op_ge,
	op_gt,
	op_lt,
	op_le,
	op_sym_eq,
	op_sym_noteq,
}               t_test;

/*
**  test functions
*/
int				check_errors(char **argv, int argc);
char			**check_inv(char **args, int *inv);
void			ft_free_ntab(char **tab);
int				free_new_argv(char **new_argv, int ret);

/*
**  Unery flag functions
*/
int				get_unary_option(char *argv);
int				check_unary_values(char *path, int flag);
int				flag_b_test(char *path);
int				flag_c_test(char *path);
int				flag_d_test(char *path);
int				flag_e_test(char *path);
int				flag_f_test(char *path);
int				flag_g_test(char *path);
int				flag_cap_l_test(char *path);
int				flag_p_test(char *path);
int				flag_r_test(char *path);
int				flag_cap_s_test(char *path);
int				flag_s_test(char *path);
int				flag_u_test(char *path);
int				flag_w_test(char *path);
int				flag_x_test(char *path);
int				flag_z_test(char *path);

/*
**  Binary flag functions
*/
int				get_binary_option(char *argv);
int				check_binary_values(char *r, char *l, int bit_flag, int *res);
int				check_longlong(char *str, long long *value);
int				flag_eq_test(char *l, char *r, int *res);
int				flag_ne_test(char *r, char *l, int *res);
int				flag_ge_test(char *r, char *l, int *res);
int				flag_gt_test(char *r, char *l, int *res);
int				flag_lt_test(char *r, char *l, int *res);
int				flag_le_test(char *r, char *l, int *res);
int				flag_sym_noteq_test(char *left, char *right, int *result);
int				flag_sym_eq_test(char *left, char *right, int *result);

#endif
