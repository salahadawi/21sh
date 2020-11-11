/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_shortcuts.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sadawi <sadawi@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/17 14:17:49 by sadawi            #+#    #+#             */
/*   Updated: 2020/04/29 13:16:50 by sadawi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

int		handle_shortcuts(char **args)
{
	int i;

	i = 0;
	while (g_21sh->builtins.shortcuts[i])
	{
		if (g_21sh->builtins.shortcuts[i](args))
			return (1);
		i++;
	}
	return (0);
}
