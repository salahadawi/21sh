/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_args.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwilen <jwilen@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/15 15:29:33 by jwilen            #+#    #+#             */
/*   Updated: 2021/03/17 08:26:12 by jwilen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hash.h"

static void	init_args(t_hash_args *hash_args)
{
	hash_args->name_index = 0;
	hash_args->opt = 0;
	hash_args->path = NULL;
	hash_args->state = get_opt;
}

static int	arg_not_an_option(char *arg, t_hash_args *hash_args)
{
	if ((arg[0] != '-' || (arg[0] == '-' && !arg[1])) &&
		hash_args->state == get_opt)
		return (1);
	return (0);
}

static int	last_args_check(t_hash_state state)
{
	if (state == get_hash_path)
	{
		ft_fprintf(STDERR_FILENO, "hash: -p: option requires an argument\n");
		ft_fprintf(STDERR_FILENO,
				"hash usage [-lr] [-p pathname] [-d] [name ...]\n");
		return (0);
	}
	return (1);
}

static int	get_option(char *arg, t_hash_args *hash_args)
{
	int		i;

	i = 0;
	while (arg[++i])
	{
		if (arg[i] == 'p' && arg[i + 1])
		{
			hash_args->path = &arg[i + 1];
			hash_args->state = get_name;
			return (1);
		}
		else if (arg[i] == 'p')
			hash_args->state = get_hash_path;
		else if (arg[i] == 'l')
			hash_args->opt = hash_args->opt | o_l;
		else if (arg[i] == 'd')
			hash_args->opt = hash_args->opt | o_d;
		else if (arg[i] == 'r')
			hash_args->opt = hash_args->opt | o_r;
		else
			return (print_invalid_option(arg[i]));
	}
	return (1);
}

int			get_args(char **args, t_hash_args *hash_args)
{
	int		i;

	init_args(hash_args);
	i = 0;
	while (args[++i])
	{
		if (arg_not_an_option(args[i], hash_args))
			hash_args->state = get_name;
		if (hash_args->state == get_name && !hash_args->name_index)
		{
			hash_args->name_index = i;
			hash_args->state = get_done;
		}
		else if (hash_args->state == get_hash_path)
		{
			hash_args->path = args[i];
			hash_args->state = get_name;
		}
		else if (args[i][0] == '-' && hash_args->state == get_opt)
		{
			if (!get_option(args[i], hash_args))
				return (0);
		}
	}
	return (last_args_check(hash_args->state));
}
