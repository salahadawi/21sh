/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shortcut_cd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sadawi <sadawi@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/17 14:11:04 by sadawi            #+#    #+#             */
/*   Updated: 2020/04/29 13:17:24 by sadawi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

int		shortcut_cd(char **args)
{
	char *oldpwd;

	oldpwd = store_oldpwd();
	if (chdir(args[0]) == -1)
	{
		free(oldpwd);
		return (0);
	}
	update_pwd();
	update_oldpwd(oldpwd);
	return (1);
}
