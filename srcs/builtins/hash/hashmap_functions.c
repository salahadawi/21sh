/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hashmap_functions.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwilen <jwilen@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/16 09:23:34 by jwilen            #+#    #+#             */
/*   Updated: 2021/03/17 08:24:52 by jwilen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hash.h"

void			map_copy(t_hashmap *previous, t_hashmap **new)
{
	t_hash_item	*item;
	t_hash_item	*prev;
	int			i;

	i = -1;
	while (++i < previous->size)
	{
		if ((item = previous->items[i]))
		{
			while (item)
			{
				prev = item;
				item = item->next;
				addto_hashmap(prev->key, prev->value, new);
			}
		}
	}
}

unsigned int	hashing(const char *key)
{
	unsigned int	address;
	unsigned int	i;

	address = 0;
	i = 0;
	while (key[i])
	{
		address = key[i] + (address << 6) + (address << 16) - address;
		i++;
	}
	return (address);
}

static void		go_forward(t_hash_item **item, t_hash_item **prev, int *len)
{
	*prev = *item;
	*item = (*item)->next;
	(*len)++;
}

char			*check_map(const char *key, t_hashmap *hashmap, t_hashopt opt)
{
	t_hash_item		*item;

	item = hashmap->items[hashing(key) % hashmap->size];
	while (item)
	{
		if (!ft_strcmp(key, item->key))
		{
			if (opt == hash_exec)
				item->count++;
			else if (opt == hash_reset)
				item->count = 0;
			return (item->value);
		}
		item = item->next;
	}
	return (NULL);
}

int				addto_hashmap(char *key, char *value, t_hashmap **hashmap)
{
	t_hash_item		*item;
	t_hash_item		*prev;
	int				i;
	int				len;

	i = hashing(key) % (*hashmap)->size;
	item = (*hashmap)->items[i];
	prev = NULL;
	len = 0;
	while (item && ft_strcmp(key, item->key))
		go_forward(&item, &prev, &len);
	if (item)
		return (replace_item(item, value));
	if (!prev)
		(*hashmap)->items[i] = create_item(key, value);
	else if (!(prev->next = create_item(key, value)))
		handle_error("Malloc failed", 1);
	if (len >= MAX_HASH)
		*hashmap = grow_up(*hashmap);
	return (1);
}
