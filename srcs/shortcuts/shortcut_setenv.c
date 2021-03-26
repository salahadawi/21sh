/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shortcut_setenv.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwilen <jwilen@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/17 14:11:32 by sadawi            #+#    #+#             */
/*   Updated: 2021/03/23 08:45:04 by jwilen           ###   ########.fr       */
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
	while (args[i] && ft_strncmp(args[i], "setenv", 6) == 0)
	{
		if (ft_strchr(args[i], '='))
		{
			add_env(args[i]);
			ft_printf("%s added to enviroment!!!\n", args[i]);
		}
		i++;
	}
	return (1);
}
