/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_alias.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jochumwilen <jochumwilen@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/21 08:02:07 by jwilen            #+#    #+#             */
/*   Updated: 2021/03/31 18:05:47 by jochumwilen      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

static void		compare_and_free(char *front, t_alias *current)
{
	if (!ft_strcmp(front, current->alias_name))
		free_alias_node(&g_21sh->alias, current);
}

void			save_command_alias(char **args)
{
	size_t	len;
	size_t	len2;
	char	*front;
	t_alias	*current;
	int		j;

	j = 0;
	current = g_21sh->alias;
	len2 = 0;
	len = len_eql(args[0]);
	while (args[j++])
		len2 += ft_strlen(args[j]);
	if (len2 > 0)
		front = produce_back_front(args, 0, len, len2);
	if (!current)
	{
		add_to_alias(args);
		return ;
	}
	while (current)
	{
		compare_and_free(front, current);
		current = current->next;
	}
	add_to_alias(args);
}

static void		print_alias(t_alias *tmp)
{
	while (tmp)
	{
		ft_fprintf(STDERR_FILENO, "%s=%s\n", tmp->alias_name, tmp->real_name);
		tmp = tmp->next;
	}
}

static void		check_alias(char *args, t_alias *tmp)
{
	while (tmp)
	{
		if (!ft_strcmp(args, tmp->alias_name))
			print_alias(tmp);
		tmp = tmp->next;
	}
}

int				builtin_alias(char **args)
{
	int			i;
	t_alias		*tmp;

	i = 1;
	tmp = g_21sh->alias;
	if (!args[1] && tmp)
		print_alias(tmp);
	while (args[i])
	{
		if (ft_strchr(args[i], EQUAL))
		{
			save_command_alias(&args[i]);
			ft_printf("%s added alias!\n", args[i]);
		}
		else if (!ft_strncmp(args[i], "-p", 2))
			print_alias(tmp);
		else if (!ft_strncmp(args[i], "-", 1))
			ft_fprintf(2, "alias: bad option: %s\n", args[i]);
		else
			check_alias(args[i], tmp);
		i++;
	}
	return (1);
}
