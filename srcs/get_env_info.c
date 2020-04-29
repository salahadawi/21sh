/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_env_info.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sadawi <sadawi@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/17 14:20:38 by sadawi            #+#    #+#             */
/*   Updated: 2020/04/29 13:13:31 by sadawi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

char	*get_env_value(char *name)
{
	int len;
	int i;

	name = strsub_alphanumeric_underscore(name);
	len = ft_strlen(name);
	i = 0;
	while (g_21sh->envp[i])
	{
		if (ft_strnequ(g_21sh->envp[i], name, len) && g_21sh->envp[i][len] == '=')
		{
			free(name);
			return (ft_strchr(g_21sh->envp[i], '=') + 1);
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
