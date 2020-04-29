/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sadawi <sadawi@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/17 14:10:22 by sadawi            #+#    #+#             */
/*   Updated: 2020/04/29 13:18:37 by sadawi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

int		builtin_cd(char **args)
{
	char *oldpwd;

	oldpwd = store_oldpwd();
	if (!args[1])
		chdir(get_env_value("HOME"));
	else if (ft_strequ(args[1], "-"))
		chdir(get_env_value("OLDPWD"));
	else
	{
		if (chdir(args[1]) == -1)
			print_error(ft_sprintf("cd: no such file or directory: %s",
			args[1]));
	}
	update_pwd();
	update_oldpwd(oldpwd);
	if (ft_strequ(args[1], "-"))
		ft_printf("%s\n", get_env_value("PWD"));
	return (1);
}

char	*store_oldpwd(void)
{
	char *path;

	path = (char*)ft_memalloc(PATH_MAX + 1);
	getcwd(path, PATH_MAX);
	return (path);
}

void	update_oldpwd(char *path)
{
	char *env_var;

	env_var = ft_strjoin("OLDPWD=", path);
	add_env(env_var);
	free(path);
	free(env_var);
}

void	update_pwd(void)
{
	char *path;
	char *env_var;

	path = (char*)ft_memalloc(PATH_MAX + 1);
	getcwd(path, PATH_MAX);
	env_var = ft_strjoin("PWD=", path);
	add_env(env_var);
	free(path);
	free(env_var);
}
