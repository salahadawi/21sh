/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_unsetenv.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sadawi <sadawi@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/17 14:09:30 by sadawi            #+#    #+#             */
/*   Updated: 2020/04/17 14:10:00 by sadawi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		builtin_unsetenv(t_env *env, char **args)
{
	int i;

	i = 1;
	while (args[i])
	{
		if (delete_env(env, args[i]))
			print_error(ft_sprintf("%s deleted from enviroment!", args[i]));
		else
			print_error(ft_sprintf("'%s' not found.", args[i]));
		i++;
	}
	return (1);
}

int		update_env(t_env *env, char **new_envp, int deleted, int i)
{
	if (deleted)
	{
		new_envp[i - deleted] = NULL;
		free(env->envp);
		env->envp = new_envp;
		return (1);
	}
	free(new_envp);
	return (0);
}

int		delete_env(t_env *env, char *arg)
{
	char	**new_envp;
	int		len;
	int		i;
	int		deleted;

	new_envp = (char**)ft_memalloc(sizeof(char*)
	* (count_env_amount(env->envp)));
	len = ft_strlen(arg);
	deleted = 0;
	i = 0;
	while (env->envp[i])
	{
		if (ft_strnequ(env->envp[i], arg, len) && env->envp[i][len] == '=')
		{
			free(env->envp[i]);
			deleted = 1;
		}
		else
			new_envp[i - deleted] = env->envp[i];
		i++;
	}
	return (update_env(env, new_envp, deleted, i));
}
