/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hash_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwilen <jwilen@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/16 08:51:23 by jwilen            #+#    #+#             */
/*   Updated: 2021/03/16 13:25:00 by jwilen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hash.h"

t_hashmap	*init_hashmap(int size)
{
	t_hashmap	*new;
	int			i;

	if (!(new = (t_hashmap*)ft_memalloc(sizeof(*new))))
		handle_error("Malloc failed", 1);
	if (!(new->items = (t_hash_item**)ft_memalloc(sizeof(t_hash_item*) * size)))
	{
		ft_memdel((void*)&new);
		handle_error("Malloc failed", 1);
	}
	new->size = size;
	i = -1;
	while (++i < new->size)
		new->items[i] = NULL;
	return (new);
}

t_hashmap	*grow_up(t_hashmap *previous)
{
	int			size;
	t_hashmap	*new;

	if (!(size = get_new_prime(previous->size)))
	{
		print_error("%s: Couldn't add to hashmap.");
		return (previous);
	}
	if (!(new = init_hashmap(size)))
		handle_error("Malloc failed", 1);
	map_copy(previous, &new);
	delete_map(previous);
	return (new);
}

t_hash_item	*create_item(const char *key, const char *value)
{
	t_hash_item	*new;

	if (!(new = (t_hash_item*)ft_memalloc(sizeof(*new))))
		handle_error("Malloc failed", 1);
	else if (new)
	{
		if (!(new->key = ft_strdup(key)))
		{
			ft_memdel((void*)&new);
			handle_error("Malloc failed", 1);
		}
		if (!(new->value = ft_strdup(value)))
		{
			ft_memdel((void*)&new->key);
			ft_memdel((void*)&new);
			handle_error("Malloc failed", 1);
		}
		new->count = 0;
		new->next = NULL;
	}
	return (new);
}
