/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hash_paths.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwilen <jwilen@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/16 12:29:37 by jwilen            #+#    #+#             */
/*   Updated: 2021/03/17 08:26:42 by jwilen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hash.h"

char				**get_paths(void)
{
	char	**paths;
	char	*path_line;

	if (!(path_line = get_env_value("PATH")))
		return (NULL);
	if (!(paths = ft_strsplit(path_line, ':')))
		handle_error("Malloc failed", 1);
	return (paths);
}

static int			check_access(const char *file)
{
	if (!file)
		return (1);
	if (access(file, F_OK) == 0)
	{
		if (access(file, X_OK) == 0)
			return (0);
		return (1);
	}
	return (1);
}

char				*find_path(const char *file, char **paths)
{
	int		i;
	char	*possible_path;
	char	*path_w_slash;

	if (!*file || !ft_strncmp(".", file, 2) || !ft_strncmp("..", file, 3)
		|| !paths)
		return (NULL);
	i = -1;
	while (paths[++i])
	{
		if (!(path_w_slash = ft_strjoin(paths[i], "/")))
			handle_error("Malloc failed", 1);
		if (!(possible_path = ft_strjoin(path_w_slash, file)))
			handle_error("Malloc failed", 1);
		ft_strdel(&path_w_slash);
		if (check_access(possible_path) == 0)
			return (possible_path);
		ft_strdel(&possible_path);
	}
	return (NULL);
}
