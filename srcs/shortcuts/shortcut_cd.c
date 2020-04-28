/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shortcut_cd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sadawi <sadawi@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/17 14:11:04 by sadawi            #+#    #+#             */
/*   Updated: 2020/04/17 14:43:15 by sadawi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		shortcut_cd(t_env *env, char **args)
{
	char *oldpwd;

	oldpwd = store_oldpwd();
	if (chdir(args[0]) == -1)
	{
		free(oldpwd);
		return (0);
	}
	update_pwd(env);
	update_oldpwd(env, oldpwd);
	return (1);
}
