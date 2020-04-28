/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sadawi <sadawi@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/17 14:10:22 by sadawi            #+#    #+#             */
/*   Updated: 2020/04/18 13:09:58 by sadawi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		builtin_cd(t_env *env, char **args)
{
	char *oldpwd;

	(void)env;
	oldpwd = store_oldpwd();
	if (!args[1])
		chdir(get_env_value(env, "HOME"));
	else if (ft_strequ(args[1], "-"))
		chdir(get_env_value(env, "OLDPWD"));
	else
	{
		if (chdir(args[1]) == -1)
			print_error(ft_sprintf("cd: no such file or directory: %s",
			args[1]));
	}
	update_pwd(env);
	update_oldpwd(env, oldpwd);
	if (ft_strequ(args[1], "-"))
		ft_printf("%s\n", get_env_value(env, "PWD"));
	return (1);
}

char	*store_oldpwd(void)
{
	char *path;

	path = (char*)ft_memalloc(PATH_MAX + 1);
	getcwd(path, PATH_MAX);
	return (path);
}

void	update_oldpwd(t_env *env, char *path)
{
	char *env_var;

	env_var = ft_strjoin("OLDPWD=", path);
	add_env(env, env_var);
	free(path);
	free(env_var);
}

void	update_pwd(t_env *env)
{
	char *path;
	char *env_var;

	path = (char*)ft_memalloc(PATH_MAX + 1);
	getcwd(path, PATH_MAX);
	env_var = ft_strjoin("PWD=", path);
	add_env(env, env_var);
	free(path);
	free(env_var);
}
