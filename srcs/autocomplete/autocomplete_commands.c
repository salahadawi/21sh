/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   autocomplete_commands.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jochumwilen <jochumwilen@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/12 09:25:45 by jwilen            #+#    #+#             */
/*   Updated: 2021/03/31 18:46:08 by jochumwilen      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

void		copy_and_escape_characters(char *dst, char *src)
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

t_autocomp	*autocomp_new_command(char *command)
{
	t_autocomp *autocomp;

	if (!(autocomp = (t_autocomp*)ft_memalloc(sizeof(t_autocomp))))
		handle_error("Malloc failed", 1);
	copy_and_escape_characters(autocomp->command, command);
	return (autocomp);
}

void		autocomp_append_command(char *command)
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

void		autocomp_commands_append_dir(char *path)
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

void		autocomplete(char **line, char previous_pressed_key)
{
	static char		*partial_command = NULL;
	static char		**matching_commands = NULL;

	if (previous_pressed_key != TAB)
	{
		free(partial_command);
		free(matching_commands);
		partial_command = get_partial_command(*line);
		if (partial_command[0] == '\0')
			matching_commands = get_dir_commands(".");
		else if (check_command_valid_dir(partial_command))
			matching_commands = get_dir_commands(partial_command);
		else
			matching_commands = get_matching_commands(partial_command);
	}
	complete_command(line, previous_pressed_key, matching_commands);
}
