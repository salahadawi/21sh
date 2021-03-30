/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_unalias.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwilen <jwilen@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/26 21:39:44 by jwilen            #+#    #+#             */
/*   Updated: 2021/03/29 15:13:54 by jwilen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

int				builtin_unalias(char **args)
{
	int			i;
	t_alias		*tmp;
	int			j;

	i = 1;
	if (!args[1])
		ft_fprintf(2, "unalias: not enough arguments\n");
	while (args[i])
	{
		j = 0;
		tmp = g_21sh->alias;
		if (!ft_strncmp(args[i], "-", 1))
			ft_fprintf(2, "unalias: bad option: %s\n", args[i]);
		while (tmp)
		{
			if (!ft_strcmp(args[i], tmp->alias_name))
			{
				free_alias_node(&g_21sh->alias, tmp);
				ft_fprintf(2, "unalias: %s deleted\n", args[i]);
				j = 1;
				break ;
			}
			tmp = tmp->next;
		}
		if (j == 0)
			ft_fprintf(2, "unalias: no such hash table element: %s\n", args[i]);
		i++;
		
	}
	return (1);
}
