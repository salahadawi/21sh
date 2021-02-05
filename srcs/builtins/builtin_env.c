/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sadawi <sadawi@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/17 14:08:01 by sadawi            #+#    #+#             */
/*   Updated: 2020/04/29 13:19:06 by sadawi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

int		builtin_env(char **args)
{
	int i;

	(void)args;
	i = 0;
	while (g_21sh->envp[i])
		ft_printf("%s\n", g_21sh->envp[i++]);
	return (1);
}
