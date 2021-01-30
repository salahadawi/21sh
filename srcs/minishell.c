/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sadawi <sadawi@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/17 14:23:12 by sadawi            #+#    #+#             */
/*   Updated: 2021/01/30 17:34:55 by sadawi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

char	*str_add_str(char *str, char *str2)
{
	int		i;
	int		index;
	char	*newstr;

	index = ft_strlen(g_21sh->line) + g_21sh->cursor.x;
	newstr = (char*)ft_memalloc(ft_strlen(str) + ft_strlen(str2) + 1); //protect
	i = 0;
	while (i < index)
	{
		newstr[i] = str[i];
		i++;
	}
	ft_strcat(newstr, str2);
	while (str[i])
	{
		newstr[i + ft_strlen(str2)] = str[i];
		i++;
	}
	newstr[i + ft_strlen(str2)] = '\0';
	return (newstr);
}

int		ft_nbrlen(int nbr)
{
	int i;

	i = 0;
	while (nbr || !i)
	{
		nbr /= 10;
		i++;
	}
	return (i);
}

void	get_cursor_position(int *x, int *y)
{
	char	sequence[100];
	int		i;

	ft_printf("%s", "\x1b[6n");
	read(0, sequence, 100);
	i = 0;
	while (sequence[i] != '[' && i < 100)
		i++;
	*y = ft_atoi(&sequence[i + 1]);
	*x = ft_atoi(&sequence[i + 2 + ft_nbrlen(*y)]);
}

void	cursor_jump_up(int *left_len)
{
	int	text_len;
	int	chars_skipped;

	text_len = g_21sh->prompt_len + ft_strlen(g_21sh->line);
	if (text_len % g_21sh->window.ws_col < abs(*left_len))
	{
		while (text_len % g_21sh->window.ws_col < abs(*left_len))
		{
			chars_skipped = text_len % g_21sh->window.ws_col;
			*left_len += chars_skipped + 1;
			text_len -= chars_skipped + 1;
			set_terminal("up");
		}
		move_cursor_right_edge();
	}
}

void	find_prompt_y(void)
{
	int i;

	i = g_21sh->cursor.prompt_y + (g_21sh->prompt_len + ft_strlen(g_21sh->line))
	 / g_21sh->window.ws_col;
	while (i-- > g_21sh->window.ws_row)
	{
		if (g_21sh->cursor.prompt_y < 1)
			return ;
		g_21sh->cursor.prompt_y--;
	}
}

void	save_cursor_position()
{
	char	sequence[100];
	int		i;
	int		x;
	int		y;

	ft_printf("%s", "\x1b[6n");
	ft_bzero(sequence, 100);
	read(0, sequence, 100);
	i = 0;
	while (sequence[i] != '[' && i < 97)
		i++;
	y = ft_atoi(&sequence[i + 1]);
	x = ft_atoi(&sequence[i + 2 + ft_nbrlen(y) < 100 ? i + 2 + ft_nbrlen(y) : 0]);
	g_21sh->cursor.prompt_y = y ? y : g_21sh->cursor.prompt_y;
	g_21sh->cursor.prompt_x = x ? x : g_21sh->cursor.prompt_x;// + g_21sh->prompt_len;
	//ft_printf("%s", &sequence[i]);
}

void	free_autocomp_commands()
{
	t_autocomp *cur;
	t_autocomp *tmp;

	cur = g_21sh->autocomp;
	while (cur)
	{
		tmp = cur;
		cur = tmp->next;
		free(tmp);	
	}
	g_21sh->autocomp = NULL;
	g_21sh->autocomp_tail = NULL;
}

int		filename_character_allowed(char c)
{
	if (!ft_isprint(c))
		return (1);
	if (ft_isalnum(c))
		return (1);
	return (c == '-' || c == '_' || c == '.');
}

void	copy_and_escape_characters(char *dst, char *src)
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

void	autocomp_append_command(char *command)
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

void	autocomp_commands_append_dir(char *path)
{
	DIR				*p_dir;
	struct dirent	*p_dirent;

	if (!(p_dir = opendir(path)))
		return ;
	while ((p_dirent = readdir(p_dir)))
	{
		if (!ft_strequ(p_dirent->d_name, ".") && !ft_strequ(p_dirent->d_name, ".."))
			autocomp_append_command(p_dirent->d_name);
	}
	closedir(p_dir);
}

void	print_autocomp_commands(void)
{
	t_autocomp *cur;
	int			i;

	i = 0;
	cur = g_21sh->autocomp;
	while (cur)
	{
		ft_printf("%d: %s\n", i++, cur->command);
		cur = cur->next;
	}
}

void	autocomplete_from_path(void)
{
	char	**paths;
	int		i;

	if (!(paths = ft_strsplit(get_env_value("PATH"), ':')))
		return ;
	i = 0;
	while (paths[i])
		autocomp_commands_append_dir(paths[i++]);
	while (i >= 0)
		free(paths[i--]);
	free(paths);
}

void	get_autocomplete_commands(void)
{
	free_autocomp_commands();
	autocomplete_from_path();
	autocomp_commands_append_dir(".");
	//print_autocomp_commands();
}

t_command	*get_next_command(void)
{
	t_command *command;

	if (!g_21sh->token || g_21sh->token->type == TOKEN_SEMI)
		return (NULL);
	while (g_21sh->token && g_21sh->token->type != TOKEN_PIPE && g_21sh->token->type != TOKEN_SEMI)
	{
		
	}

	if (g_21sh->token && g_21sh->token->type == TOKEN_PIPE)
		g_21sh->token = g_21sh->token->next;
}

t_command	*get_commands(void)
{
	t_command	*commands;
	t_command	*tmp;

	commands = NULL;
	while (1)
	{
		if (!commands)
		{
			tmp = get_next_command();
			commands = tmp;
		}
		else
		{
			tmp->next = get_next_command();
			tmp = tmp->next;
		}
		if (!tmp)
			break ;
	}
	return (commands);
}

void	run_commands(void)
{
	t_command	*commands;

	while (g_21sh->token) // handle set of tokens at a time, split by ;
	{
		commands = get_commands();
		run_commands(commands);
	}
}

void	loop_shell(void)
{
	char	**commands;
	char	**args;
	int		loop;
	int		i;
	t_token	*current;

	loop = 1;
	get_history_file_path();
	while (loop)
	{
		open_history_file();
		g_21sh->cursor.x = 0;
		//set_terminal(NORMAL_MODE);
		print_shell_info();
		get_autocomplete_commands();
		if (get_input() < 1)
		{
			break ; //never breaks???
		}
		save_command_history();
		lexi();
		current = g_21sh->token; // for debug printing, delete later
		//parsing_check(&g_21sh->token); // Disabled for now, checks if line of tokens is valid
		while (current)
		{
			ft_printf("\ntoken: %d %s\n", current->type,current->value);
			//ft_printf("\ntoken: *token: %p *value: %p prev:%p next:%p type: %d value:%s\n",current, current->value, current->prev, current->next, current->type, current->value);
			current = current->next;
		}
	
		//run_commands();
		//check_cmd(); // write somekind of ast tree or grammar, then execute commands
		
		free_history();
		// free(commands);
		free(g_21sh->line);
		set_terminal(SPECIAL_MODE); //what is this for??
	}
}

int		check_cmd()
{

	// if (!g_21sh->token)
	//	return (1);
	// handle_expansion();
	run_first();
	return (0);
}
