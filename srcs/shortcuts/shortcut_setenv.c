/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shortcut_setenv.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sadawi <sadawi@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/17 14:11:32 by sadawi            #+#    #+#             */
/*   Updated: 2021/02/05 14:12:32 by sadawi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

int		shortcut_setenv(char **args)
{
	int i;

	i = 0;
	while (args[i])
	{
		if (!ft_strchr(args[i++], '='))
			return (0);
	}
	i = 0;
	while (args[i])
	{
		if (ft_strchr(args[i], '='))
		{
			add_env(args[i]);
			ft_printf("%s added to enviroment!\n", args[i]);
		}
		i++;
	}
	return (1);
}
