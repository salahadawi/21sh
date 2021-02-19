/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_unsetenv.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwilen <jwilen@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/17 14:09:30 by sadawi            #+#    #+#             */
/*   Updated: 2021/02/19 10:22:15 by jwilen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

int		builtin_unsetenv(char **args)
{
	int i;

	i = 1;
	while (args[i])
	{
		if (delete_env(args[i]))
			print_error(ft_sprintf("%s deleted from enviroment!", args[i]));
		else
			print_error(ft_sprintf("'%s' not found.", args[i]));
		i++;
	}
	return (1);
}

int		update_env(char **new_envp, int deleted, int i)
{
	if (deleted)
	{
		new_envp[i - deleted] = NULL;
		free(g_21sh->envp);
		g_21sh->envp = new_envp;
		return (1);
	}
	free(new_envp);
	return (0);
}

int		delete_env(char *arg)
{
	char	**new_envp;
	int		len;
	int		i;
	int		deleted;

	new_envp = (char**)ft_memalloc(sizeof(char*)
	* (count_env_amount(g_21sh->envp)));
	len = ft_strlen(arg);
	deleted = 0;
	i = 0;
	while (g_21sh->envp[i])
	{
		if (ft_strnequ(g_21sh->envp[i], arg, len) &&
		g_21sh->envp[i][len] == '=')
		{
			free(g_21sh->envp[i]);
			deleted = 1;
		}
		else
			new_envp[i - deleted] = g_21sh->envp[i];
		i++;
	}
	return (update_env(new_envp, deleted, i));
}
