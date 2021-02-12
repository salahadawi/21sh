/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   autocomplete_commands.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwilen <jwilen@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/12 09:25:45 by jwilen            #+#    #+#             */
/*   Updated: 2021/02/12 13:54:55 by jwilen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

int				filename_character_allowed(char c)
{
	if (!ft_isprint(c))
		return (1);
	if (ft_isalnum(c))
		return (1);
	return (c == '-' || c == '_' || c == '.');
}

void			copy_and_escape_characters(char *dst, char *src)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (src[i])
	{
		if (!filename_character_allowed(src[i]))
		{
			dst[i + j] = '\\';
			j++;
		}
		dst[i + j] = src[i];
		i++;
	}
}

t_autocomp		*autocomp_new_command(char *command)
{
	t_autocomp *autocomp;

	if (!(autocomp = (t_autocomp*)ft_memalloc(sizeof(t_autocomp))))
		handle_error("Malloc failed", 1);
	copy_and_escape_characters(autocomp->command, command);
	return (autocomp);
}

void			autocomp_append_command(char *command)
{
	if (!g_21sh->autocomp)
	{
		g_21sh->autocomp = autocomp_new_command(command);
		g_21sh->autocomp_tail = g_21sh->autocomp;
	}
	else
	{
		g_21sh->autocomp_tail->next = autocomp_new_command(command);
		g_21sh->autocomp_tail = g_21sh->autocomp_tail->next;
	}
}

void			autocomp_commands_append_dir(char *path)
{
	DIR				*p_dir;
	struct dirent	*p_dirent;

	if (!(p_dir = opendir(path)))
		return ;
	while ((p_dirent = readdir(p_dir)))
	{
		if (!ft_strequ(p_dirent->d_name, ".") &&
		!ft_strequ(p_dirent->d_name, ".."))
			autocomp_append_command(p_dirent->d_name);
	}
	closedir(p_dir);
}
