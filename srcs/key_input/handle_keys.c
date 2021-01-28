/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_keys.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sadawi <sadawi@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/11 15:43:13 by jwilen            #+#    #+#             */
/*   Updated: 2021/01/28 15:50:36 by sadawi           ###   ########.fr       */
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

void	complete_command(char **matching_commands)
{
	char		*final_string;
	int			i;
	int			len;
	static int	j;

	if (!matching_commands || !(*matching_commands))
		return ;
	if (g_21sh->previous_pressed_key != TAB)
		j = 0;
	len = ft_strlen(g_21sh->line) - 1;
	i = len;
	i = find_start_of_command_index(g_21sh->line, i);
	final_string = ft_strjoinfree(ft_strsub(g_21sh->line, 0, i + 1), ft_strdup(matching_commands[j]));
	j = (!matching_commands[j] || !matching_commands[j + 1]) ? 0 : j + 1;
	free(g_21sh->line);
	g_21sh->line = final_string;
}

DIR		*open_dir_until_last_slash(char *path)
{
	DIR *p_dir;
	char *tmp;

	if ((p_dir = opendir(path)))
		return (p_dir);
	if (ft_strrchr(path, '/'))
	{
		tmp = ft_strdup(path);
		*ft_strrchr(tmp, '/') = '\0';
	}
	else
		tmp = ft_strdup(path);
	p_dir = opendir(tmp);
	free(tmp);
	return (p_dir);
}

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
	new_str = (char*)ft_memalloc(i + j + 1);
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

char	*join_path_and_filename(char *path, char *filename)
{
	DIR		*p_dir;
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
	tmp = ft_strjoinfree(tmp, ft_strdup_and_escape_characters(filename));
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
		if (match_with_input_after_slash(path, p_dirent->d_name))
		{
			tmp = commands;
			commands = (char**)ft_memalloc(sizeof(char*) * (size + 1));
			if (tmp)
				ft_memcpy(commands, tmp, size * sizeof(char*));
			commands[size++ - 1] = join_path_and_filename(path, p_dirent->d_name);
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
		*ft_strrchr(tmp, '/') = '\0';
	}
	else
		tmp = ft_strdup(command);
	if (!(p_dir = opendir(tmp))) // segfault ??
	{
		free(tmp);
		return (0);
	}
	closedir(p_dir);
	free(tmp);
	return (1);
}

void	autocomplete(void)
{
	static char	*partial_command;
	static char	**matching_commands;

	if (g_21sh->previous_pressed_key != TAB)
	{
		partial_command = get_partial_command();
		if (partial_command[0] == '\0')
			matching_commands = get_dir_commands("./");
		else if (check_command_valid_dir(partial_command)) //CLOSE DIR
		{
			matching_commands = get_dir_commands(partial_command);
		}
		else
			matching_commands = get_matching_commands(partial_command);
	}
	complete_command(matching_commands);
	//free matching commands
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