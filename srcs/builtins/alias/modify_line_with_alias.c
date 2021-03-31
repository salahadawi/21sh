/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   modify_line_with_alias.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jochumwilen <jochumwilen@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/28 20:32:00 by jwilen            #+#    #+#             */
/*   Updated: 2021/03/31 18:11:01 by jochumwilen      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/sh.h"

int			len_eql(char *arg)
{
	int		i;

	i = 0;
	while (ft_strchr(&arg[i], '=') != 0)
		i++;
	return (i);
}

int			check_while(int i)
{
	if (ft_strncmp(&g_21sh->line[i], " ", 1) != 0)
		return (1);
	else if ((ft_strnequ(&g_21sh->line[i], ";", 1) != 0))
		return (1);
	return (0);
}

static void	compare_line(char *str, t_alias *current, int i)
{
	if ((!ft_strcmp(str, current->alias_name)))
	{
		ft_memmove(&g_21sh->line[i], str, i);
		free(str);
	}
}

void		modify_line_with_alias(void)
{
	int			i;
	int			j;
	int			k;
	char		*str;
	t_alias		*current;

	i = 0;
	j = 0;
	k = 0;
	while ((&g_21sh->line[j]) && (ft_strlen(g_21sh->line) > (size_t)j))
	{
		while (check_while(i++) != 0)
			j++;
		if (!(str = (char*)ft_memalloc(i + 1)))
			handle_error("Malloc failed", 1);
		ft_strncpy(str, g_21sh->line, i);
		current = g_21sh->alias;
		while (current)
		{
			compare_line(str, current, i);
			current = current->next;
		}
		j++;
	}
}
