/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_shortcuts.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sadawi <sadawi@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/17 14:17:49 by sadawi            #+#    #+#             */
/*   Updated: 2020/04/29 12:49:20 by sadawi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

int		handle_shortcuts(t_env *env, char **args)
{
	int i;

	i = 0;
	while (env->shortcut_funcs[i])
	{
		if (env->shortcut_funcs[i](env, args))
			return (1);
		i++;
	}
	return (0);
}
