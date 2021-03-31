/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_builtins.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jochumwilen <jochumwilen@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/17 14:19:51 by sadawi            #+#    #+#             */
/*   Updated: 2021/03/31 17:58:51 by jochumwilen      ###   ########.fr       */
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
