/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extra_functions.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwilen <jwilen@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/08 11:12:26 by jwilen            #+#    #+#             */
/*   Updated: 2021/03/08 14:14:58 by jwilen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

void		free_paths(char **paths, int i)
{
	while (paths[i])
		free(paths[i++]);
}

char		*adding_str_to_newstr(char *newstr, char *str, int index)
{
	int		i;

	i = 0;
	while (i < index)
	{
		newstr[i] = str[i];
		i++;
	}
	if (!str[i])
	{
		free(str);
		return (newstr);
	}
	while (str[i + 1])
	{
		newstr[i] = str[i + 1];
		i++;
	}
	newstr[i] = '\0';
	return (newstr);
}

char		*adding_str_to_paste(int index, char *newstr,
			char *str, char *paste)
{
	int		i;
	int		j;

	i = 0;
	while (i < index)
	{
		newstr[i] = str[i];
		i++;
	}
	j = 0;
	while (paste[j])
	{
		newstr[i] = paste[j];
		i++;
		j++;
	}
	while (str[i - j])
	{
		newstr[i] = str[i - j];
		i++;
	}
	newstr[i] = '\0';
	return (newstr);
}
