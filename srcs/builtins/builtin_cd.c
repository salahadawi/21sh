/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwilen <jwilen@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/17 14:10:22 by sadawi            #+#    #+#             */
/*   Updated: 2021/03/08 09:19:41 by jwilen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

int		builtin_cd(char **args)
{
	char 	*oldpwd;

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
		// else if (access(args[1], X_OK) != 0)
		// 	print_error(ft_sprintf("cd: permission denied: %s", args[1]));
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

	if (!(path = (char*)ft_memalloc(PATH_MAX + 1)))
		handle_error("Malloc failed", 1);
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

	if (!(path = (char*)ft_memalloc(PATH_MAX + 1)))
		handle_error("Malloc failed", 1);
	getcwd(path, PATH_MAX);
	env_var = ft_strjoin("PWD=", path);
	add_env(env_var);
	free(path);
	free(env_var);
}
