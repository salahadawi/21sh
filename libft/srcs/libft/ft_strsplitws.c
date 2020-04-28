/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplitws.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sadawi <sadawi@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/22 17:38:13 by sadawi            #+#    #+#             */
/*   Updated: 2020/04/17 17:27:38 by sadawi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

static char	*ft_strchrnonull(const char *s, int c)
{
	int i;

	i = 0;
	while (s[i])
	{
		if (s[i] == c)
			return ((char*)&s[i]);
		i++;
	}
	return (NULL);
}

static	int	count_strings(char *str, char *whitespace)
{
	int i;
	int j;

	i = 0;
	j = 0;
	while (ft_strchrnonull(whitespace, str[j]))
		j++;
	if (str[j] == '\0')
		return (0);
	while (str[j + 1])
	{
		if (ft_strchrnonull(whitespace, str[j])
		&& !ft_strchrnonull(whitespace, str[j + 1]))
			i++;
		j++;
	}
	return (i + 1);
}

static char	*string(char *s, char *whitespace, int index)
{
	int		i;
	int		j;
	int		strindex;
	char	*str;

	i = 0;
	j = 0;
	strindex = 0;
	while (ft_strchrnonull(whitespace, s[i]))
		i++;
	while (strindex < index)
	{
		while (!ft_strchrnonull(whitespace, s[i]) && s[i])
			i++;
		while (ft_strchrnonull(whitespace, s[i]))
			i++;
		strindex++;
	}
	if (!(s[i]))
		return (NULL);
	while (!ft_strchrnonull(whitespace, s[i + j]) && s[i + j] != '\0')
		j++;
	return (str = ft_strsub(s, i, j));
}

char		**ft_strsplitws(const char *s)
{
	char	**arr;
	char	*whitespace;
	int		i;

	whitespace = " \t\n\r\v\f\"\'";
	i = 0;
	if (!(arr = (char**)ft_memalloc(sizeof(arr) *
		count_strings((char*)s, whitespace) + 1)))
		return (NULL);
	while ((arr[i] = string((char*)s, whitespace, i)))
		i++;
	arr[i] = 0;
	return (arr);
}
