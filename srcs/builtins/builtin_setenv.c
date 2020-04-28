/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_setenv.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sadawi <sadawi@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/17 14:08:24 by sadawi            #+#    #+#             */
/*   Updated: 2020/04/17 14:09:18 by sadawi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		builtin_setenv(t_env *env, char **args)
{
	int i;

	i = 1;
	while (args[i])
	{
		if (ft_strchr(args[i], '='))
		{
			add_env(env, args[i]);
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

void	add_env(t_env *env, char *arg)
{
	char	**new_envp;
	int		i;

	new_envp = (char**)ft_memalloc(sizeof(char*)
	* (count_env_amount(env->envp) + 2));
	i = 0;
	while (env->envp[i])
	{
		if (check_names_match(env->envp[i], arg))
		{
			free(env->envp[i]);
			env->envp[i] = ft_strdup(arg);
			free(new_envp);
			return ;
		}
		else
			new_envp[i] = env->envp[i];
		i++;
	}
	new_envp[i] = ft_strdup(arg);
	new_envp[i + 1] = NULL;
	free(env->envp);
	env->envp = new_envp;
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
