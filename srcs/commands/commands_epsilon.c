/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands_epsilon.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwilen <jwilen@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/22 11:30:56 by jwilen            #+#    #+#             */
/*   Updated: 2021/02/22 11:42:02 by jwilen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

char	*get_partial_command(char *line)
{
	int i;
	int len;

	len = ft_strlen(line) - 1;
	i = len;
	while (i >= 0 && line[i] != ' ')
		i--;
	return (ft_strsub(line, i + 1, len - i));
}

char	**get_matching_commands(char *part_command)
{
	char		**matching_commands;
	t_autocomp	*cur;
	int			i;

	i = 0;
	cur = g_21sh->autocomp;
	while (cur)
	{
		if (ft_strnequ(cur->command, part_command, ft_strlen(part_command)))
			i++;
		cur = cur->next;
	}
	if (!i)
		return (NULL);
	if (!(matching_commands = ft_memalloc(sizeof(char*) * (i + 1))))
		handle_error("Malloc failed", 1);
	i = 0;
	cur = g_21sh->autocomp;
	while (cur)
	{
		if (ft_strnequ(cur->command, part_command, ft_strlen(part_command)))
			matching_commands[i++] = cur->command;
		cur = cur->next;
	}
	return (matching_commands);
}

int		find_start_of_command_index(char *str, int end_index)
{
	while (end_index >= 0)
	{
		if (str[end_index] == ' ')
			if (end_index > 0 && str[end_index - 1] != '\\')
				break ;
		end_index--;
	}
	return (end_index);
}

void	complete_command(char **line, char previous_pressed_key,
char **matching_commands)
{
	char		*final_string;
	int			i;
	int			len;
	static int	j;

	if (!matching_commands || !(*matching_commands))
		return ;
	if (previous_pressed_key != TAB)
		j = 0;
	len = ft_strlen(*line) - 1;
	i = len;
	i = find_start_of_command_index(*line, i);
	final_string = ft_strjoinfree(ft_strsub(*line, 0, i + 1),
	ft_strdup(matching_commands[j]));
	j = (!matching_commands[j] || !matching_commands[j + 1]) ? 0 : j + 1;
	free(*line);
	*line = final_string;
}

DIR		*open_dir_until_last_slash(char *path)
{
	DIR		*p_dir;
	char	*tmp;

	if ((p_dir = opendir(path)))
		return (p_dir);
	if (ft_strrchr(path, '/'))
	{
		tmp = ft_strdup(path);
		*(ft_strrchr(tmp, '/') + 1) = '\0';
	}
	else
		tmp = ft_strdup(path);
	p_dir = opendir(tmp);
	free(tmp);
	return (p_dir);
}
