/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_env_info.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sadawi <sadawi@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/17 14:20:38 by sadawi            #+#    #+#             */
/*   Updated: 2020/04/17 14:21:08 by sadawi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_env_value(t_env *env, char *name)
{
	int len;
	int i;

	name = strsub_alphanumeric_underscore(name);
	len = ft_strlen(name);
	i = 0;
	while (env->envp[i])
	{
		if (ft_strnequ(env->envp[i], name, len) && env->envp[i][len] == '=')
		{
			free(name);
			return (ft_strchr(env->envp[i], '=') + 1);
		}
		i++;
	}
	free(name);
	return (NULL);
}

int		get_env_name_len(char *str)
{
	int i;

	i = 0;
	while (str[i] && (ft_isalnum(str[i]) || str[i] == '_'))
		i++;
	return (i);
}

int		count_env_amount(char *envp[])
{
	int i;

	i = 0;
	while (envp[i])
		i++;
	return (i);
}
