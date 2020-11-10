/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_input.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwilen <jwilen@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/17 14:16:04 by sadawi            #+#    #+#             */
/*   Updated: 2020/11/10 14:10:32 by jwilen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"



void	handle_expansion()
{
	char	*ptr;
	int		i;
	t_tok	*current;

	i = 0;
	current = g_21sh->token;
	while (current)
	{
		if (current->str[0] == '~')
			current->str = expand_tilde(current->str, &current->str[0]);
		if ((ptr = find_dollar(current->str)) && ptr + 1)
			current->str = expand_dollar(current->str, ptr);
		current = current->next;
	}
}

char	*expand_tilde(char *str, char *ptr)
{
	char	*expanded_str;
	char	*value;
	int		len;

	if (ptr == str)
		expanded_str = ft_strjoin(get_env_value("HOME"), ptr + 1);
	else
	{
		len = find_size_pointers(str, ptr);
		value = ft_strdup(get_env_value("HOME"));
		expanded_str = ft_strjoinfree(ft_strsub(str, 0, len), value);
		len = 1;
		expanded_str = ft_strjoinfree(expanded_str, ft_strdup(ptr + len));
	}
	free(str);
	return (expanded_str);
}

char	*expand_dollar(char *str, char *ptr)
{
	char	*expanded_str;
	char	*value;
	int		len;

	len = find_size_pointers(str, ptr);
	value = ft_strdup(get_env_value(ptr + 1));
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
