/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hash_main.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwilen <jwilen@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/15 14:23:59 by jwilen            #+#    #+#             */
/*   Updated: 2021/03/17 08:22:05 by jwilen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/sh.h"
#include "hash.h"
#include "test.h"

static int	add_name(t_hash_args *hash_args, int argc, char **args)
{
	int		ret;
	int		i;
	char	**paths;
	char	*value;

	ret = 0;
	i = hash_args->name_index - 1;
	paths = get_paths();
	while (++i < argc)
	{
		if (ft_strchr(args[i], '/'))
			continue ;
		if (!(value = find_path(args[i], paths)))
		{
			print_error(ft_sprintf("42sh: hash: %s not found", args[i]));
			ret = 1;
		}
		else
		{
			addto_hashmap(args[i], value, &g_21sh->hashmap);
			ft_strdel(&value);
		}
	}
	ft_free_ntab(paths);
	return (ret);
}

static void	add_name_path(t_hashmap **hashmap, t_hash_args *hash_args,
			int argc, char **argv)
{
	int		i;

	i = hash_args->name_index - 1;
	while (++i < argc)
	{
		if (ft_strchr(argv[i], '/'))
			continue ;
		addto_hashmap(argv[i], hash_args->path, hashmap);
	}
}

static int	drop_name(t_hashmap **hashmap, t_hash_args *hash_args,
			int argc, char **args)
{
	int		i;
	int		ret;

	i = hash_args->name_index - 1;
	ret = 0;
	while (++i < argc)
	{
		if (!drop_item(args[i], *hashmap))
		{
			print_error(ft_sprintf("42sh: hash: %s not found", args[i]));
			ret = 1;
		}
	}
	return (ret);
}

int			hash_builtin(int argc, char **args)
{
	t_hash_args		hash_args;

	if (argc == 1)
	{
		print_hashmap(g_21sh->hashmap);
		return (0);
	}
	if (!get_args(args, &hash_args))
		return (2);
	if (hash_args.opt & o_r)
		reset_hash(&g_21sh->hashmap);
	if (hash_args.path && hash_args.name_index)
		add_name_path(&g_21sh->hashmap, &hash_args, argc, args);
	else if (hash_args.opt & o_d && hash_args.name_index)
		return (drop_name(&g_21sh->hashmap, &hash_args, argc, args));
	else if ((!hash_args.opt || hash_args.opt & o_r) && hash_args.name_index)
		return (add_name(&hash_args, argc, args));
	else if (!(hash_args.opt & o_r))
		return (hash_print(g_21sh->hashmap, &hash_args, argc, args));
	return (0);
}
