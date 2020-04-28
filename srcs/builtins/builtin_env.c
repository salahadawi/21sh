/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sadawi <sadawi@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/17 14:08:01 by sadawi            #+#    #+#             */
/*   Updated: 2020/04/17 14:41:36 by sadawi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		builtin_env(t_env *env, char **args)
{
	int i;

	(void)args;
	i = 0;
	while (env->envp[i])
		ft_printf("%s\n", env->envp[i++]);
	return (1);
}
