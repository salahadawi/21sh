/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands_delta.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwilen <jwilen@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/22 11:25:13 by jwilen            #+#    #+#             */
/*   Updated: 2021/03/05 11:56:08 by jwilen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

char	*ft_strdup_and_escape_characters(char *str)
{
	char	*new_str;
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (str[i])
		if (!filename_character_allowed(str[i++]))
			j++;
	if (!(new_str = (char*)ft_memalloc(i + j + 1)))
		handle_error("Malloc failed", 1);
	i = 0;
	j = 0;
	while (str[i])
	{
		if (!filename_character_allowed(str[i]))
		{
			new_str[i + j] = '\\';
			j++;
		}
		new_str[i + j] = str[i];
		i++;
	}
	return (new_str);
}

char	*join_path_and_filename(char *path, struct dirent *p_dirent)
{
	char	*tmp;

	if (ft_strequ(path, "."))
		tmp = NULL;
	else
	{
		tmp = ft_strdup(path);
		if (ft_strrchr(path, '/'))
			*ft_strrchr(tmp, '/') = '\0';
		tmp = ft_strjoinfree(tmp, ft_strdup("/"));
	}
	tmp = ft_strjoinfree(tmp,
	ft_strdup_and_escape_characters(p_dirent->d_name));
	if (p_dirent->d_type == DT_DIR)
		tmp = ft_strjoinfree(tmp, ft_strdup("/"));
	return (tmp);
}

int		match_with_input_after_slash(char *path, char *command)
{
	char *tmp;

	if ((tmp = ft_strrchr(path, '/')))
	{
		tmp++;
		return (ft_strnequ(tmp, command, ft_strlen(tmp)));
	}
	return (1);
}

char	**get_dir_commands(char *path)
{
	DIR				*p_dir;
	struct dirent	*p_dirent;
	char			**commands;
	char			**tmp;
	int				size;

	if (!(p_dir = open_dir_until_last_slash(path)))
		handle_error("Opening current directory failed", 1);
	commands = NULL;
	size = 1;
	while ((p_dirent = readdir(p_dir)))
	{
		if (match_with_input_after_slash(path, p_dirent->d_name) &&
		!ft_strequ(p_dirent->d_name, ".") && !ft_strequ(p_dirent->d_name, ".."))
		{
			tmp = commands;
			commands = (char**)ft_memalloc(sizeof(char*) * (size + 1));
			if (tmp)
				ft_memcpy(commands, tmp, size * sizeof(char*));
			commands[size++ - 1] = join_path_and_filename(path, p_dirent);
		}
	}
	closedir(p_dir);
	return (commands);
}

int		check_command_valid_dir(char *command)
{
	DIR		*p_dir;
	char	*tmp;

	if (ft_strrchr(command, '/'))
	{
		tmp = ft_strdup(command);
		*(ft_strrchr(tmp, '/') + 1) = '\0';
	}
	else
		tmp = ft_strdup(command);
	if (!(p_dir = opendir(tmp)))
	{
		free(tmp);
		return (0);
	}
	closedir(p_dir);
	free(tmp);
	return (1);
}
