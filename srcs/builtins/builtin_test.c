/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_test.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwilen <jwilen@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/11 15:37:49 by jwilen            #+#    #+#             */
/*   Updated: 2021/03/15 09:42:17 by jwilen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/sh.h"
#include "test.h"

static int	return_inv(int ret, int inv)
{
	if (inv % 2)
		return (!ret);
	return (ret);
}

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

int			builtin_test(char **args)
{
	int		argc;
	int		flag;
	int		inv;
	int		ret;
	char	**new_argv;
	int i = 0;

	initilize_inits(&argc, &flag, &inv);
	new_argv = check_inv(args, &inv);
	while (new_argv[argc])
		argc++;
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
	while (new_argv[i])
	{
		print_error(ft_sprintf("%s\n", new_argv[i]));
		i++;
	}
	
	return (free_new_argv(new_argv, return_inv(ret, inv)));
}