/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_unalias.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jochumwilen <jochumwilen@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/26 21:39:44 by jwilen            #+#    #+#             */
/*   Updated: 2021/03/31 18:23:05 by jochumwilen      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

static int		delete_alias_un(char **args, int i, t_alias *tmp)
{
	if (!ft_strcmp(args[i], tmp->alias_name))
	{
		free_alias_node(&g_21sh->alias, tmp);
		ft_fprintf(2, "unalias: %s deleted\n", args[i]);
		return (1);
	}
	return (0);
}

int				builtin_unalias(char **args)
{
	t_alias		*tmp;
	int			i;
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
			j = delete_alias_un(args, i, tmp);
			tmp = tmp->next;
		}
		if (j == 0)
			ft_fprintf(2, "unalias: no such hash table element: %s\n", args[i]);
		i++;
	}
	return (1);
}
