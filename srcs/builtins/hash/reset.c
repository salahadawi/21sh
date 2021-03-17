/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwilen <jwilen@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/16 08:39:01 by jwilen            #+#    #+#             */
/*   Updated: 2021/03/17 08:23:44 by jwilen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hash.h"

int			drop_item(const char *key, t_hashmap *hashmap)
{
	t_hash_item	*item;
	t_hash_item	*prev;
	int			i;

	if (!check_map(key, hashmap, hash_check))
		return (0);
	i = hashing(key) % hashmap->size;
	item = hashmap->items[i];
	prev = NULL;
	while (item && ft_strcmp(key, item->key))
	{
		prev = item;
		item = item->next;
	}
	if (prev)
		prev->next = item->next;
	else
		hashmap->items[i] = item->next;
	delete_item(item);
	return (1);
}

int			replace_item(t_hash_item *item, const char *value)
{
	if (!ft_strcmp(value, item->value))
		item->count = 0;
	else
	{
		ft_memdel((void*)&item->value);
		if (!(item->value = ft_strdup(value)))
			handle_error("Malloc failed", 1);
		item->count = 0;
	}
	return (1);
}

void		delete_item(t_hash_item *item)
{
	ft_memdel((void*)&item->key);
	ft_memdel((void*)&item->value);
	ft_memdel((void*)&item);
}

void		delete_map(t_hashmap *hashmap)
{
	int				i;
	t_hash_item		*item;
	t_hash_item		*prev;

	i = -1;
	while (++i < hashmap->size)
	{
		if (hashmap->items[i])
		{
			item = hashmap->items[i];
			while (item)
			{
				prev = item;
				item = item->next;
				delete_item(prev);
			}
		}
	}
	ft_memdel((void*)&hashmap->items);
	ft_memdel((void*)&hashmap);
}

int			reset_hash(t_hashmap **hashmap)
{
	t_hashmap	*new;

	delete_map(*hashmap);
	if (!(new = init_hashmap(INIT_SIZE)))
		handle_error("Malloc failed", 1);
	*hashmap = new;
	return (1);
}
