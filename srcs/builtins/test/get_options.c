/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_options.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwilen <jwilen@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/15 09:33:48 by jwilen            #+#    #+#             */
/*   Updated: 2021/03/15 12:14:21 by jwilen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test.h"

int			check_errors(char **argv, int argc)
{
	int		ret;

	ret = 0;
	if (argc > 4)
	{
		print_error(ft_sprintf("42sh: test: too many arguments"));
		ret = 2;
	}
	else if (argc == 3 && get_unary_option(argv[1]) == -1)
	{
		print_error(ft_sprintf("42sh: test: %s: unary operation expected",
		argv[1]));
		ret = 2;
	}
	else if (argc == 4 && get_binary_option(argv[2]) == -1)
	{
		print_error(ft_sprintf("42sh: test: %s: unary operation expected",
		argv[2]));
		ret = 2;
	}
	return (ret);
}

/*
**	( EXPRESSION )
**		EXPRESSION is true
**	! EXPRESSION
**		EXPRESSION is false
**	-z STRING
**		the length of STRING is zero
**	STRING1 = STRING2
**		the strings are equal
**	STRING1 != STRING2
**		the strings are not equal
**	INTEGER1 -eq INTEGER2
**		INTEGER1 is equal to INTEGER2
**	INTEGER1 -ge INTEGER2
**		INTEGER1 is greater than or equal to INTEGER2
**	INTEGER1 -gt INTEGER2
**		INTEGER1 is greater than INTEGER2
**	INTEGER1 -le INTEGER2
**		INTEGER1 is less than or equal to INTEGER2
**	INTEGER1 -lt INTEGER2
**		INTEGER1 is less than INTEGER2
**	INTEGER1 -ne INTEGER2
**		INTEGER1 is not equal to INTEGER2
**	-b FILE
**		FILE exists and is block special
**	-c FILE
**		FILE exists and is character special
**	-d FILE
**		FILE exists and is a directory
**	-e FILE
**		FILE exists
**	-f FILE
**		FILE exists and is a regular file
**	-g FILE
**		FILE exists and is set-group-ID
**	-L FILE
**		FILE exists and is a symbolic link (same as -h)
**	-p FILE
**		FILE exists and is a named pipe
**	-r FILE
**		FILE exists and read permission is granted
**	-s FILE
**		FILE exists and has a size greater than zero
**	-S FILE
**		FILE exists and is a socket
**	-u FILE
**		FILE exists and its set-user-ID bit is set
**	-w FILE
**		FILE exists and write permission is granted
**	-x FILE
**		FILE exists and execute (or search) permission is granted
*/

int			get_binary_option(char *argv)
{
	if (!ft_strcmp(argv, "="))
		return (op_sym_eq);
	else if (!ft_strcmp(argv, "!="))
		return (op_sym_noteq);
	else if (!ft_strcmp(argv, "-eq"))
		return (op_eq);
	else if (!ft_strcmp(argv, "-ne"))
		return (op_ne);
	else if (!ft_strcmp(argv, "-ge"))
		return (op_ge);
	else if (!ft_strcmp(argv, "-gt"))
		return (op_gt);
	else if (!ft_strcmp(argv, "-lt"))
		return (op_lt);
	else if (!ft_strcmp(argv, "-le"))
		return (op_le);
	return (-1);
}

static int	get_unary_option_alfa(char *argv)
{
	if (!ft_strcmp(argv, "-p"))
		return (flag_p);
	if (!ft_strcmp(argv, "-r"))
		return (flag_r);
	if (!ft_strcmp(argv, "-s"))
		return (flag_s);
	if (!ft_strcmp(argv, "-S"))
		return (flag_cap_s);
	if (!ft_strcmp(argv, "-u"))
		return (flag_u);
	if (!ft_strcmp(argv, "-w"))
		return (flag_w);
	if (!ft_strcmp(argv, "-x"))
		return (flag_x);
	if (!ft_strcmp(argv, "-z"))
		return (flag_z);
	return (-1);
}

int			get_unary_option(char *argv)
{
	if (!ft_strcmp(argv, "-b"))
		return (flag_b);
	if (!ft_strcmp(argv, "-c"))
		return (flag_c);
	if (!ft_strcmp(argv, "-d"))
		return (flag_d);
	if (!ft_strcmp(argv, "-e"))
		return (flag_e);
	if (!ft_strcmp(argv, "-f"))
		return (flag_f);
	if (!ft_strcmp(argv, "-g"))
		return (flag_g);
	if (!ft_strcmp(argv, "-L"))
		return (flag_cap_l);
	return (get_unary_option_alfa(argv));
}
