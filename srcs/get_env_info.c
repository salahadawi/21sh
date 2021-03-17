/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_env_info.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwilen <jwilen@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/17 14:20:38 by sadawi            #+#    #+#             */
/*   Updated: 2021/03/16 08:19:19 by jwilen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

// static	int		ft_strcmp_before_c(char *search, char *str, char c)
// {
// 	int		i;

// 	if (!search || !str || !c)
// 		return (0);
// 	i = -1;
// 	while (str[++i] && str[i] != c && search[i])
// 	{
// 		if (str[i] != search[i])
// 			return (0);
// 	}
// 	if (!search[i] && str[i] == c)
// 		return (i);
// 	else
// 		return (0);
// }

// char			*get_envline_value(char *search, char **env)
// {
// 	int		i;
// 	int		offset;

// 	if (!search)
// 		return (NULL);
// 	i = -1;
// 	while (env && env[++i])
// 	{
// 		if ((offset = ft_strcmp_before_c(search, env[i], '=')))
// 			return (&(env[i][offset + 1]));
// 	}
// 	return (NULL);
// }

char			*get_env_value(char *name)
{
	int len;
	int i;

	name = strsub_alphanumeric_underscore(name);
	len = ft_strlen(name);
	i = 0;
	while (g_21sh->envp[i])
	{
		if (ft_strnequ(g_21sh->envp[i], name, len) &&
		g_21sh->envp[i][len] == '=')
		{
			free(name);
			return (ft_strchr(g_21sh->envp[i], '=') + 1);
		}
		i++;
	}
	free(name);
	return (NULL);
}

int				get_env_name_len(char *str)
{
	int i;

	i = 0;
	while (str[i] && (ft_isalnum(str[i]) || str[i] == '_'))
		i++;
	return (i);
}

int				count_env_amount(char *envp[])
{
	int i;

	i = 0;
	while (envp[i])
		i++;
	return (i);
}
