/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_shell.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sadawi <sadawi@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/17 14:12:23 by sadawi            #+#    #+#             */
/*   Updated: 2021/01/12 13:41:37 by sadawi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

void	init_env(char *envp[])
{
	int i;

	i = count_env_amount(envp);
	g_21sh->envp = (char**)ft_memalloc(sizeof(char*) * (i + 1)); //protect all mallocs
	i = 0;
	while (envp[i])
	{
		g_21sh->envp[i] = ft_strdup(envp[i]);
		i++;
	}
	g_21sh->envp[i] = NULL;
	init_builtins();
	init_shortcuts();
}

void	init_builtins(void)
{
	char	*builtin_names;
	int		count;

	builtin_names = "echo exit env setenv unsetenv cd";
	g_21sh->builtins.names = ft_strsplit(builtin_names, ' ');
	count = 0;
	while (g_21sh->builtins.names[count])
		count++;
	g_21sh->builtins.funcs = (t_builtin_func**)ft_memalloc(sizeof(t_builtin_func*)
	* count);
	g_21sh->builtins.funcs[0] = &builtin_echo;
	g_21sh->builtins.funcs[1] = &builtin_exit;
	g_21sh->builtins.funcs[2] = &builtin_env;
	g_21sh->builtins.funcs[3] = &builtin_setenv;
	g_21sh->builtins.funcs[4] = &builtin_unsetenv;
	g_21sh->builtins.funcs[5] = &builtin_cd;
}

/*
** When adding a new shortcut function, add +1 to count
*/

void	init_shortcuts(void)
{
	int		count;

	count = 2;
	g_21sh->builtins.shortcuts = (t_shortcut_func**)ft_memalloc(
		sizeof(t_shortcut_func*) * (count + 1));
	g_21sh->builtins.shortcuts[0] = &shortcut_cd;
	g_21sh->builtins.shortcuts[1] = &shortcut_setenv;
	g_21sh->builtins.shortcuts[2] = NULL;
}

void	clear_screen(void)
{
	char **args;

	args = (char**)ft_memalloc(sizeof(char*) * 2); //protect
	args[0] = ft_strdup("clear");
	args[1] = NULL;
	exec_cmd(args);
	free(args[0]);
	free(args);
}
