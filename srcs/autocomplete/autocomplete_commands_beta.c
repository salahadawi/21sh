/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   autocomplete_commands_beta.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwilen <jwilen@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/12 13:50:00 by jwilen            #+#    #+#             */
/*   Updated: 2021/02/12 13:56:56 by jwilen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

void		print_autocomp_commands(void)
{
	t_autocomp	*cur;
	int			i;

	i = 0;
	cur = g_21sh->autocomp;
	while (cur)
	{
		ft_printf("%d: %s\n", i++, cur->command);
		cur = cur->next;
	}
}

void		free_autocomp_commands(void)
{
	t_autocomp *cur;
	t_autocomp *tmp;

	cur = g_21sh->autocomp;
	while (cur)
	{
		tmp = cur;
		cur = tmp->next;
		free(tmp);
	}
	g_21sh->autocomp = NULL;
	g_21sh->autocomp_tail = NULL;
}

void		autocomplete_from_path(void)
{
	char	**paths;
	int		i;

	if (!(paths = ft_strsplit(get_env_value("PATH"), ':')))
		return ;
	i = 0;
	while (paths[i])
		autocomp_commands_append_dir(paths[i++]);
	while (i >= 0)
		free(paths[i--]);
	free(paths);
}
