/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_shell.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sadawi <sadawi@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/17 14:12:23 by sadawi            #+#    #+#             */
/*   Updated: 2020/04/17 14:59:53 by sadawi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_env(t_env **env, char *envp[])
{
	int i;

	i = count_env_amount(envp);
	(*env) = (t_env*)ft_memalloc(sizeof(t_env));
	(*env)->envp = (char**)ft_memalloc(sizeof(char*) * (i + 1));
	i = 0;
	while (envp[i])
	{
		(*env)->envp[i] = ft_strdup(envp[i]);
		i++;
	}
	(*env)->envp[i] = NULL;
	init_builtins(*env);
	init_shortcuts(*env);
}

void	init_builtins(t_env *env)
{
	char	*builtin_names;
	int		count;

	builtin_names = "echo exit env setenv unsetenv cd";
	env->builtin_names = ft_strsplit(builtin_names, ' ');
	count = 0;
	while (env->builtin_names[count])
		count++;
	env->builtin_funcs = (t_builtin_func**)ft_memalloc(sizeof(t_builtin_func*)
	* count);
	env->builtin_funcs[0] = &builtin_echo;
	env->builtin_funcs[1] = &builtin_exit;
	env->builtin_funcs[2] = &builtin_env;
	env->builtin_funcs[3] = &builtin_setenv;
	env->builtin_funcs[4] = &builtin_unsetenv;
	env->builtin_funcs[5] = &builtin_cd;
}

/*
** When adding a new shortcut function, add +1 to count
*/

void	init_shortcuts(t_env *env)
{
	int		count;

	count = 2;
	env->shortcut_funcs = (t_shortcut_func**)ft_memalloc(
		sizeof(t_shortcut_func*) * (count + 1));
	env->shortcut_funcs[0] = &shortcut_cd;
	env->shortcut_funcs[1] = &shortcut_setenv;
	env->shortcut_funcs[2] = NULL;
}

void	clear_screen(t_env *env)
{
	char **args;

	args = (char**)ft_memalloc(sizeof(char*) * 2);
	args[0] = ft_strdup("clear");
	args[1] = NULL;
	exec_cmd(env, args);
	free(args[0]);
	free(args);
}
