/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hash_print.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwilen <jwilen@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/15 14:37:15 by jwilen            #+#    #+#             */
/*   Updated: 2021/03/17 08:19:01 by jwilen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hash.h"

static int	hashmap_empty(t_hashmap *hashmap)
{
	int		empty;
	int		i;

	empty = 1;
	i = -1;
	while (++i < (int)hashmap->size)
	{
		if (hashmap->items[i])
			empty = 0;
	}
	if (empty)
		print_error(ft_sprintf("hash: hash table empty"));
	return (empty);
}

void		print_hashmap(t_hashmap *hashmap)
{
	t_hash_item		*item;
	int				i;

	if (hashmap_empty(hashmap))
		return ;
	ft_fprintf(STDERR_FILENO, "hits\tcommand\n");
	i = -1;
	while (++i < (int)hashmap->size)
	{
		item = hashmap->items[i];
		while (item)
		{
			ft_fprintf(STDERR_FILENO, "%4d\t%s\n", item->count, item->value);
			item = item->next;
		}
	}
}

int			print_hashmap_l_args(t_hashmap *hashmap, t_hash_args *hash_args,
			int argc, char **args)
{
	int			ret;
	int			i;
	const char	*value;

	i = hash_args->name_index - 1;
	ret = 0;
	while (++i < argc)
	{
		if ((value = check_map(args[i], hashmap, hash_check)))
			ft_sprintf("hash -p %s %s\n", value, args[i]);
		else
		{
			print_error(ft_sprintf("hash: %s: not found", args[i]));
			ret = 1;
		}
	}
	return (ret);
}

void		print_hashmap_l(t_hashmap *hashmap)
{
	int			i;
	t_hash_item	*item;

	if (hashmap_empty(hashmap))
		return ;
	i = -1;
	while (++i < (int)hashmap->size)
	{
		item = hashmap->items[i];
		while (item)
		{
			ft_fprintf(STDERR_FILENO, "hash -p %s %s\n",
				item->value, item->key);
			item = item->next;
		}
	}
}

int			hash_print(t_hashmap *hashmap, t_hash_args *hash_args,
			int argc, char **args)
{
	if (hash_args->opt & o_l)
	{
		if (!hash_args->name_index)
			print_hashmap_l(hashmap);
		else
			return (print_hashmap_l_args(hashmap, hash_args, argc, args));
	}
	else
		print_hashmap(hashmap);
	return (0);
}
