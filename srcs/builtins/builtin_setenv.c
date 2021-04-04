/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_setenv.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sadawi <sadawi@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/17 14:08:24 by sadawi            #+#    #+#             */
/*   Updated: 2021/04/04 17:56:23 by sadawi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

int		builtin_setenv(char **args)
{
	int i;

	i = 1;
	while (args[i])
	{
		if (ft_strchr(args[i], EQUAL))
		{
			add_env(args[i]);
			print_error(ft_sprintf("%s added to enviroment!", args[i]));
		}
		else
		{
			print_error(ft_sprintf("'%s' could not be added.", args[i]));
			print_error(ft_sprintf("Correct format: NAME=value"));
		}
		i++;
	}
	return (1);
}

void	add_env(char *arg)
{
	char	**new_envp;
	int		i;

	if (!(new_envp = (char**)ft_memalloc(sizeof(char*)
	* (count_env_amount(g_21sh->envp) + 2))))
		handle_error("Malloc failed", 1);
	i = 0;
	while (g_21sh->envp[i])
	{
		if (check_names_match(g_21sh->envp[i], arg))
		{
			free(g_21sh->envp[i]);
			g_21sh->envp[i] = ft_strdup(arg);
			free(new_envp);
			return ;
		}
		else
			new_envp[i] = g_21sh->envp[i];
		i++;
	}
	new_envp[i] = ft_strdup(arg);
	new_envp[i + 1] = NULL;
	free(g_21sh->envp);
	g_21sh->envp = new_envp;
}

int		check_names_match(char *var1, char *var2)
{
	int i;

	i = 0;
	while (var1[i] && var2[i])
	{
		if (var1[i] != var2[i])
			return (0);
		if (var1[i] == '=' && var2[i] == '=')
			return (1);
		i++;
	}
	return (0);
}
