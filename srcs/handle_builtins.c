/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_builtins.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sadawi <sadawi@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/17 14:19:51 by sadawi            #+#    #+#             */
/*   Updated: 2020/04/17 14:20:04 by sadawi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		handle_builtins(t_env *env, char **args)
{
	int i;

	i = 0;
	while (env->builtin_names[i])
	{
		if (ft_strequ(env->builtin_names[i], args[0]))
			return (env->builtin_funcs[i](env, args));
		i++;
	}
	return (handle_shortcuts(env, args));
}
