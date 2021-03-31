/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_test.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jochumwilen <jochumwilen@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/11 15:37:49 by jwilen            #+#    #+#             */
/*   Updated: 2021/03/31 18:26:09 by jochumwilen      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/sh.h"
#include "test.h"

static int	no_arg(char **new_argv, int argc, int inv)
{
	if ((argc == 1 && !new_argv[argc]) || !new_argv[argc - 1][0])
		return (free_new_argv(new_argv, return_inv(1, inv)));
	return (free_new_argv(new_argv, return_inv(0, inv)));
}

static void	initilize_inits(int *a, int *b, int *c)
{
	*a = 0;
	*b = 0;
	*c = 0;
}

static void	print_new_argv(char **new_argv)
{
	int		i;

	i = 0;
	while (new_argv[i])
	{
		print_error(ft_sprintf("%s\n", new_argv[i]));
		i++;
	}
}

static int	count_argc(char **new_argv)
{
	int		i;

	i = 0;
	while (new_argv[i])
		i++;
	return (i);
}

int			builtin_test(char **args)
{
	int		argc;
	int		flag;
	int		inv;
	int		ret;
	char	**new_argv;

	initilize_inits(&argc, &flag, &inv);
	new_argv = check_inv(args, &inv);
	argc = count_argc(new_argv);
	if ((ret = check_errors(new_argv, argc)))
		return (free_new_argv(new_argv, ret));
	if (argc == 1 || argc == 2)
		return (no_arg(new_argv, argc, inv));
	else if (argc == 3)
		flag = get_unary_option(new_argv[1]);
	else if (argc == 4)
		flag = get_binary_option(new_argv[2]);
	if (flag <= flag_z)
		ret = check_unary_values(new_argv[2], flag);
	else if (flag > flag_z)
		if (check_binary_values(new_argv[1], new_argv[3], flag, &ret))
			return (free_new_argv(new_argv, 2));
	print_error(ft_sprintf("%d %d", flag, return_inv(ret, inv)));
	print_new_argv(new_argv);
	return (free_new_argv(new_argv, return_inv(ret, inv)));
}
