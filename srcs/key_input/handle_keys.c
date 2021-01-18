/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_keys.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sadawi <sadawi@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/11 15:43:13 by jwilen            #+#    #+#             */
/*   Updated: 2021/01/18 17:29:02 by sadawi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

void	handle_backspace(void)
{
	g_21sh->line = str_remove_char(g_21sh->line, ft_strlen(g_21sh->line)
	+ g_21sh->cursor.x - 1);
}

void	handle_control_sequence(char *c)
{
	*c += 100;
	
	if (*c == g_21sh->key_sequences.delete_key)
		handle_delete();
	else if (*c == g_21sh->key_sequences.left_arrow)
		move_cursor_left();
	else if (*c == g_21sh->key_sequences.right_arrow)
		move_cursor_right();
	else if (*c == g_21sh->key_sequences.up_arrow)
		get_history_prev();
	else if (*c == g_21sh->key_sequences.down_arrow)
		get_history_next();
	else if (*c == HOME)
		g_21sh->cursor.x = -ft_strlen(g_21sh->line);
	else if (*c == END)
		g_21sh->cursor.x = 0;
	else if (*c + 10 == g_21sh->key_sequences.left_arrow)
		move_word_left();
	else if (*c + 10 == g_21sh->key_sequences.right_arrow)
		move_word_right();
	else if (*c + 10 == g_21sh->key_sequences.up_arrow)
		move_cursor_up();//copy_input();
	else if (*c + 10 == g_21sh->key_sequences.down_arrow)
		move_cursor_down();//paste_input();
}

char	*get_partial_command(void)
{
	int i;
	int len;

	len = ft_strlen(g_21sh->line) - 1;
	i = len;
	while (i >= 0 && g_21sh->line[i] != ' ')
		i--;
	return (ft_strsub(g_21sh->line, i + 1, len - i));
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

void	complete_command(char **matching_commands)
{
	char		*final_string;
	int			i;
	int			len;
	static int	j;

	len = ft_strlen(g_21sh->line) - 1;
	i = len;
	while (i >= 0 && g_21sh->line[i] != ' ')
		i--;
	final_string = ft_strjoinfree(ft_strsub(g_21sh->line, 0, i + 1), ft_strdup(matching_commands[j]));
	j = (!matching_commands[j] || !matching_commands[j + 1]) ? 0 : j + 1;
	free(g_21sh->line);
	g_21sh->line = final_string;
}

char	**get_dir_commands(char *path)
{
	DIR				*p_dir;
	struct dirent	*p_dirent;
	char			**commands;
	char			**tmp;
	int				size;

	if (!(p_dir = opendir(path)))
		handle_error("Opening current directory failed", 1);
	commands = NULL;
	size = 1;
	while ((p_dirent = readdir(p_dir)))
	{
		if (!commands)
		{
			commands = (char**)ft_memalloc(sizeof(char*) * (size++ + 1));
			commands[0] = p_dirent->d_name;
		}
		else
		{
			tmp = commands;
			commands = (char**)ft_memalloc(sizeof(char*) * (size + 1));
			ft_memcpy(commands, tmp, size * sizeof(char*));
			commands[size - 1] = p_dirent->d_name;
			size++;
		}
	}
	closedir(p_dir);
	return (commands);
}

void	autocomplete(void)
{
	static char	*partial_command;
	static char	**matching_commands;

	if (g_21sh->previous_pressed_key != TAB)
	{
		partial_command = get_partial_command();
		if (partial_command[0] == '\0')
			matching_commands = get_dir_commands(".");
		else
			matching_commands = get_matching_commands(partial_command);
	}
	complete_command(matching_commands);
}

int		handle_keys(void)
{
	char c;

	c = read_key();
	// ft_printf("%d", c);
	if (c == 0)
		return (1);
	if (c < 0)
	{
		handle_control_sequence(&c);
		return (1);
	}
	if (c == BACKSPACE)
	{
		handle_backspace();
	}
	else if (c == ENTER)
		return (0);
	else if (c == TAB)
	{
		autocomplete();
	}
	else if (c == 4)
	{
		restore_terminal_mode();
		exit(0); //temporary, need to restore terminal and free memory here
	}
	else if (ft_isprint(c))
		g_21sh->line = str_add_char(g_21sh->line, c);
	g_21sh->previous_pressed_key = c;
	return (1);
}