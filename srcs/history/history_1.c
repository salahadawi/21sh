/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history_1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwilen <jwilen@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/11 15:50:27 by jwilen            #+#    #+#             */
/*   Updated: 2020/11/11 15:51:58 by jwilen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

int		file_is_empty(void)
{
	 struct stat stats;
	 if (stat(g_21sh->history_file_path, &stats))
		return (1);
	if(stats.st_size <= 1)
		return (1);
	return (0);
}

void	open_history_file(void)
{
	char *line;

	g_21sh->history = NULL;
	g_21sh->history_fd = open(g_21sh->history_file_path,
		O_RDWR | O_APPEND | O_CREAT, 0666);
	if (g_21sh->history_fd == -1)
		return ;
	if (!file_is_empty())
	{
		while (get_next_line(g_21sh->history_fd, &line) > 0)
			add_to_history(line);
	}
	add_to_history(ft_strdup(""));
}

int		input_just_whitespace(void)
{
	int i;

	i = 0;
	while (g_21sh->line[i])
		if (!ft_strchr(" \t\n\v\f\r",g_21sh->line[i++]))
			return (0);
	return (1);
}

void	save_command_history(void)
{
	if (ft_strlen(g_21sh->line) > 100)
		return ;
	if (g_21sh->history_fd != -1)
		if (!same_as_previous_command() && !input_just_whitespace())
			ft_putendl_fd(g_21sh->line, g_21sh->history_fd);
}

void	get_history_file_path(void)
{
	char *path;

	path = (char*)ft_memalloc(PATH_MAX + 1);
	getcwd(path, PATH_MAX);
	path = ft_strjoinfree(path, ft_strdup("/.21sh_history"));
	g_21sh->history_file_path = path;
}