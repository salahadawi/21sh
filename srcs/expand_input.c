/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_input.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sadawi <sadawi@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/17 14:16:04 by sadawi            #+#    #+#             */
/*   Updated: 2020/04/17 14:17:33 by sadawi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_expansion(t_env *env, char **args)
{
	char	*ptr;
	int		i;

	i = 0;
	while (args[i])
	{
		if (args[i][0] == '~')
			args[i] = expand_tilde(env, args[i], &args[i][0]);
		else if ((ptr = ft_strchr(args[i], '~')))
			args[i] = expand_tilde(env, args[i], ptr);
		i++;
	}
	i = 0;
	while (args[i])
	{
		if ((ptr = find_dollar(args[i])) && ptr + 1)
			args[i] = expand_dollar(env, args[i], ptr);
		else
			i++;
	}
}

char	*expand_tilde(t_env *env, char *str, char *ptr)
{
	char	*expanded_str;
	char	*value;
	int		len;

	if (ptr == str)
		expanded_str = ft_strjoin(get_env_value(env, "HOME"), ptr + 1);
	else
	{
		len = find_size_pointers(str, ptr);
		value = ft_strdup(get_env_value(env, "HOME"));
		expanded_str = ft_strjoinfree(ft_strsub(str, 0, len), value);
		len = 1;
		expanded_str = ft_strjoinfree(expanded_str, ft_strdup(ptr + len));
	}
	free(str);
	return (expanded_str);
}

char	*expand_dollar(t_env *env, char *str, char *ptr)
{
	char	*expanded_str;
	char	*value;
	int		len;

	len = find_size_pointers(str, ptr);
	value = ft_strdup(get_env_value(env, ptr + 1));
	expanded_str = ft_strjoinfree(ft_strsub(str, 0, len), value);
	len = get_env_name_len(ptr + 1);
	expanded_str = ft_strjoinfree(expanded_str, ft_strdup(ptr + 1 + len));
	free(str);
	return (expanded_str);
}

char	*find_dollar(const char *s)
{
	int i;

	i = 0;
	while (s[i])
	{
		if (s[i] == '$')
			return ((char*)&s[i]);
		i++;
	}
	return (NULL);
}
