/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_builtins.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwilen <jwilen@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/17 14:19:51 by sadawi            #+#    #+#             */
/*   Updated: 2021/03/14 17:50:44 by jwilen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

int		handle_builtins(char **args)
{
	int i;

	i = 0;
	while (g_21sh->builtins.names[i])
	{
		if (ft_strequ(g_21sh->builtins.names[i], args[0]))
			return (g_21sh->builtins.funcs[i](args));
		i++;
	}
	return (handle_shortcuts(args));
}
