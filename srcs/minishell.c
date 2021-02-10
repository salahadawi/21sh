/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sadawi <sadawi@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/17 14:23:12 by sadawi            #+#    #+#             */
/*   Updated: 2021/02/10 14:53:58 by sadawi           ###   ########.fr       */
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

void	free_token(t_token *token)
{
	free(token->value);
	free(token->heredoc);
	free(token);
}

int		advance_tokens(void)
{
	t_token *tmp;

	if (!g_21sh->token)
		return (0);
	
	tmp = g_21sh->token->next;
	free_token(g_21sh->token);
	g_21sh->token = tmp;
	return (!!tmp);
}

t_arg		*new_arg(void)
{
	t_arg *arg;

	if (!(arg = (t_arg*)ft_memalloc(sizeof(t_arg))))
		handle_error("Malloc failed", 1);
	arg->word = ft_strdup(g_21sh->token->value);
	advance_tokens();
	return (arg);
}

t_redir		*new_redir(void)
{
	t_redir *redir;

	if (!(redir = (t_redir*)ft_memalloc(sizeof(t_redir))))
		handle_error("Malloc failed", 1);
	redir->type = g_21sh->token->type;
	if (advance_tokens())
	{
		redir->word = ft_strdup(g_21sh->token->value);
		advance_tokens();
	}
	return (redir);
}



t_redir		*new_redir_aggregation(void)
{
	t_redir *redir;

	if (!(redir = (t_redir*)ft_memalloc(sizeof(t_redir))))
		handle_error("Malloc failed", 1);
	if (ft_isdigit(g_21sh->token->value[0]))
		redir->word = ft_itoa(ft_atoi(g_21sh->token->value));
	else
		redir->word = NULL;
	redir->type = g_21sh->token->type;
	if (advance_tokens())
		redir->word2 = ft_strdup(g_21sh->token->value);
	advance_tokens();
	return (redir);
}

int		check_token_redir()
{
	return (g_21sh->token->type == TOKEN_LRGER
	|| g_21sh->token->type == TOKEN_SMLER
	|| g_21sh->token->type == TOKEN_INSERTION
	|| g_21sh->token->type == TOKEN_EXTRACTION);
}

void	add_arg(t_command *command)
{
	static t_arg *cur_arg;

	if (!command->arguments)
	{
		cur_arg = new_arg();
		command->arguments = cur_arg;
	}
	else
	{
		cur_arg->next = new_arg();
		cur_arg = cur_arg->next;
	}
}

void	add_redir(t_command *command, int aggregation)
{
	static t_redir *cur_redir;

	if (!command->redirections)
	{
		if (aggregation)
			cur_redir = new_redir_aggregation();
		else
			cur_redir = new_redir();
		command->redirections = cur_redir;
	}
	else
	{
		if (aggregation)
			cur_redir->next = new_redir_aggregation();
		else
			cur_redir->next = new_redir();
		cur_redir = cur_redir->next;
	}
}

int		check_token_fd_aggregation()
{
	return (g_21sh->token->type == TOKEN_SMALER_ET
	|| g_21sh->token->type == TOKEN_LRGER_ET);
}

t_command	*get_next_command(void)
{
	t_command	*command;
	t_redir		*cur_redir;
	t_arg		*cur_arg;
	

	if (!g_21sh->token || g_21sh->token->type == TOKEN_SEMI)
		return (NULL);
	if (!(command = (t_command*)ft_memalloc(sizeof(t_command))))
		handle_error("Malloc failed", 1);
	while (g_21sh->token && g_21sh->token->type != TOKEN_PIPE && g_21sh->token->type != TOKEN_SEMI)
	{
		if (check_token_fd_aggregation())
			add_redir(command, AGGREGATION);
		else if (check_token_redir())
			add_redir(command, NO_AGGREGATION);
		else
			add_arg(command);
	}
	if (g_21sh->token && g_21sh->token->type == TOKEN_PIPE)
		g_21sh->token = g_21sh->token->next;
	return (command);
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

char	*token_type_to_char(int type) //causes leaks with print_commands, for debug purposes
{
	if (type == TOKEN_LRGER)
		return (ft_strdup(">"));
	if (type == TOKEN_SMLER)
		return (ft_strdup("<"));
	if (type == TOKEN_EXTRACTION)
		return (ft_strdup(">>"));
	if (type == TOKEN_INSERTION)
		return (ft_strdup("<<"));
	return ("ERROR");
}

void	print_commands(t_command *commands)
{
	t_command	*tmp_command;
	t_arg		*tmp_arg;
	t_redir		*tmp_redir;
	int			i;

	i = 1;
	tmp_command = commands;
	while (tmp_command)
	{
		tmp_arg = tmp_command->arguments;
		tmp_redir = tmp_command->redirections;
		ft_printf("Command %d:\n", i++);
		if (tmp_arg)
			ft_printf("Arguments: ");
		while (tmp_arg)
		{
			ft_printf("%s ", tmp_arg->word);
			tmp_arg = tmp_arg->next;
		}
		if (tmp_redir)
			ft_printf("\nRedirections: ");
		while (tmp_redir)
		{
			ft_printf("Type: %s, File: %s ", token_type_to_char(tmp_redir->type), tmp_redir->word);
			tmp_redir = tmp_redir->next;
		}
		ft_printf("\n");
		tmp_command = tmp_command->next;
	}
	ft_printf("\n");
}

size_t	commands_amount(t_command *commands)
{
	t_command	*tmp;
	size_t		i;

	i = 0;
	tmp = commands;
	while (tmp)
	{
		tmp = tmp->next;
		i++;
	}
	return (i);
}

int		*get_pipes(t_command *commands)
{
	int		*pipes;
	size_t	pipe_amount;
	size_t	i;

	pipe_amount = (commands_amount(commands) - 1) * 2;
	if (!pipe_amount)
		return (NULL);
	pipes = (int*)ft_memalloc(sizeof(int) * (pipe_amount + 1));
	i = 0;
	while (i < pipe_amount)
	{
		pipe(&(pipes[i]));
		i += 2;
	}
	pipes[i] = -1;
	return (pipes);
}

void	redirect_output_to_file_truncate(char *file)
{
	int fd;

	fd = open(file, O_TRUNC | O_RDWR | O_CREAT, 0666);
	close(STDOUT_FILENO);
	dup2(fd, STDOUT_FILENO);
}

void	redirect_output_to_file_append(char *file)
{
	int fd;

	fd = open(file, O_APPEND | O_RDWR | O_CREAT, 0666);
	close(STDOUT_FILENO);
	dup2(fd, STDOUT_FILENO);
}

void	redirect_file_to_input(char *file)
{
	int fd;

	if ((fd = open(file, O_RDWR)) == -1)
	{
		ft_fprintf(STDERR_FILENO, "No such file or directory: %s\n", file);
		exit(1);
	}
	close(STDIN_FILENO);
	dup2(fd, STDIN_FILENO);
}

void	handle_delete_heredoc(char **line)
{
	*line = str_remove_char(*line, ft_strlen(*line)
	+ g_21sh->cursor_heredoc.x);
	move_cursor_right();
}

void	move_cursor_left_heredoc(char **line)
{
	if ((int)ft_strlen(*line) > -g_21sh->cursor_heredoc.x)
		g_21sh->cursor_heredoc.x--;
}

void	move_cursor_right_heredoc(char **line)
{
	if (g_21sh->cursor_heredoc.x < 0)
		g_21sh->cursor_heredoc.x++;
}

void	get_history_prev_heredoc(char **line)
{
	if (g_21sh->history)
		if (g_21sh->history->prev)
		{
			free(*line);
			g_21sh->history = g_21sh->history->prev;
			*line = ft_strdup(g_21sh->history->cmd);
			g_21sh->cursor_heredoc.x = 0;
		}
}

void	get_history_next_heredoc(char **line)
{
	if (g_21sh->history)
		if (g_21sh->history->next)
		{
			free(*line);
			g_21sh->history = g_21sh->history->next;
			*line = ft_strdup(g_21sh->history->cmd);
			g_21sh->cursor_heredoc.x = 0;
		}
}

void	move_word_left_heredoc(char **line)
{
	int i;

	i = ft_strlen(*line);
	i += g_21sh->cursor_heredoc.x;
	while (i > 0)
	{
		if (ft_strchr(" \t\n\v\f\r", (*line)[i - 1]))
			move_cursor_left_heredoc(line);
		else
			break;
		i--;
	}
	while (i > 0)
	{
		if (!ft_strchr(" \t\n\v\f\r", (*line)[i - 1]))
			move_cursor_left_heredoc(line);
		else
			break;
		i--;
	}
}

void	move_word_right_heredoc(char **line)
{
	int i;
	int len;

	len = ft_strlen(*line);
	i = len;
	i += g_21sh->cursor_heredoc.x;
	while (i < len)
	{
		if (!ft_strchr(" \t\n\v\f\r", (*line)[i]))
			move_cursor_right_heredoc(line);
		else
			break;
		i++;
	}
	while (i < len)
	{
		if (ft_strchr(" \t\n\v\f\r", (*line)[i]))
			move_cursor_right_heredoc(line);
		else
			break;
		i++;
	}
}

void	move_cursor_up_heredoc(char **line)
{
	if ((int)ft_strlen(*line) + g_21sh->cursor_heredoc.x >= g_21sh->window.ws_col)
		g_21sh->cursor_heredoc.x -= g_21sh->window.ws_col;
}

void	move_cursor_down_heredoc(void)
{
	if (-g_21sh->cursor_heredoc.x >= g_21sh->window.ws_col)
		g_21sh->cursor_heredoc.x += g_21sh->window.ws_col;
}

void	handle_control_sequence_heredoc(char **line, char *c)
{
	*c += 100;
	
	if (*c == g_21sh->key_sequences.delete_key)
		handle_delete_heredoc(line);
	else if (*c == g_21sh->key_sequences.left_arrow)
		move_cursor_left_heredoc(line);
	else if (*c == g_21sh->key_sequences.right_arrow)
		move_cursor_right_heredoc(line);
	else if (*c == g_21sh->key_sequences.up_arrow)
		get_history_prev_heredoc(line);
	else if (*c == g_21sh->key_sequences.down_arrow)
		get_history_next_heredoc(line);
	else if (*c == HOME)
		g_21sh->cursor_heredoc.x = -ft_strlen(*line);
	else if (*c == END)
		g_21sh->cursor_heredoc.x = 0;
	else if (*c + 10 == g_21sh->key_sequences.left_arrow)
		move_word_left_heredoc(line);
	else if (*c + 10 == g_21sh->key_sequences.right_arrow)
		move_word_right_heredoc(line);
	else if (*c + 10 == g_21sh->key_sequences.up_arrow)
		move_cursor_up_heredoc(line);//copy_input();
	else if (*c + 10 == g_21sh->key_sequences.down_arrow)
		move_cursor_down_heredoc();//paste_input();
}

char	*str_add_char_heredoc(char **str, char c)
{
	int		i;
	int		index;
	char	*newstr;

	index = ft_strlen(*str) + g_21sh->cursor_heredoc.x;
	newstr = (char*)ft_memalloc(ft_strlen(*str) + 2); //protect
	i = 0;
	while (i < index)
	{
		newstr[i] = (*str)[i];
		i++;
	}
	newstr[i] = c;
	while ((*str)[i])
	{
		newstr[i + 1] = (*str)[i];
		i++;
	}
	newstr[i + 1] = '\0';
	free(*str);
	return (newstr);
}

char	*str_remove_char_heredoc(char **str, int index)
{
	int		i;
	char	*newstr;

	if (index < 0 || index >= (int)ft_strlen(*str))
		return (*str);
	newstr = (char*)ft_memalloc(ft_strlen(*str));
	i = 0;
	while (i < index)
	{
		newstr[i] = (*str)[i];
		i++;
	}
	if (!(*str)[i])
	{
		free(*str);
		return (newstr);
	}
	while ((*str)[i + 1])
	{
		newstr[i] = (*str)[i + 1];
		i++;
	}
	newstr[i] = '\0';
	free(*str);
	return (newstr);
}


void	handle_backspace_heredoc(char **line)
{
	*line = str_remove_char_heredoc(line, ft_strlen(*line)
	+ g_21sh->cursor_heredoc.x - 1);
}

int		handle_keys_heredoc(char **line, char *previous_pressed_key)
{
	char c;

	c = read_key();
	// ft_printf("%d", c);
	if (c == 0)
		return (1);
	if (c < 0)
	{
		handle_control_sequence_heredoc(line, &c);
		return (1);
	}
	if (c == BACKSPACE)
	{
		handle_backspace_heredoc(line);
	}
	else if (c == ENTER)
		return (0);
	else if (c == TAB)
	{
		autocomplete(line, *previous_pressed_key);
	}
	else if (c == 4) // CTRL + D
	{
		//restore_terminal_mode();
		return (-1); //temporary, need to restore terminal and free memory here
	}
	else if (ft_isprint(c))
		*line = str_add_char_heredoc(line, c);
	*previous_pressed_key = c;
	return (1);
}

void	save_cursor_position_heredoc()
{
	char	sequence[100];
	int		i;
	int		x;
	int		y;

	ft_fprintf(g_21sh->stdout, "%s", "\x1b[6n");
	ft_bzero(sequence, 100);
	read(g_21sh->stdin, sequence, 100);
	i = 0;
	while (sequence[i] != '[' && i < 97)
		i++;
	y = ft_atoi(&sequence[i + 1]);
	x = ft_atoi(&sequence[i + 2 + ft_nbrlen(y) < 100 ? i + 2 + ft_nbrlen(y) : 0]);
	g_21sh->cursor_heredoc.prompt_y = y ? y : g_21sh->cursor_heredoc.prompt_y;
	g_21sh->cursor_heredoc.prompt_x = x ? x : g_21sh->cursor_heredoc.prompt_x;// + g_21sh->prompt_len;
	//ft_printf("%s", &sequence[i]);
}

int		input_too_large_heredoc(char **line)
{
	if (ft_strlen(*line) > 100000)
	{
		free(*line);
		ft_fprintf(2, "\nError: Input exceeds ARG_MAX.");
		*line = ft_strdup("");
		return (1);
	}
	return (0);
}

void	move_cursor_start_heredoc(void)
{
	char *move_cursor;
	char *tmp;

	move_cursor = tgetstr("cm", NULL);
	//ft_printf("%d, %d", g_21sh->cursor.prompt_y, g_21sh->cursor.prompt_x);
	tmp = tgoto(move_cursor, g_21sh->cursor_heredoc.prompt_x - 1, g_21sh->cursor_heredoc.prompt_y - 1);
	tputs(tmp, 1, ft_putschar);
}

void	print_input_heredoc(char *line)
{
	int len;
	int max_len;
	int	index;

	len = ft_strlen("heredoc> ") + ft_strlen(line);
	max_len = g_21sh->window.ws_col * g_21sh->window.ws_row;
	if (len > max_len)
	{
		index = 0;
		while (len - index > max_len)
			index += g_21sh->window.ws_col;
		index += g_21sh->window.ws_col - ft_strlen("heredoc> ");
		//len -= max_len;
		//len += g_21sh->window.ws_col;
		ft_fprintf(g_21sh->stdout, "...\n%s", &line[index]);
	}
	else
		ft_fprintf(g_21sh->stdout, "%s", line);
}

void	move_cursor_next_line_heredoc(char *line)
{
	if (ft_strlen("heredoc> ") + (int)ft_strlen(line)
		< g_21sh->window.ws_col * g_21sh->window.ws_row)
	{
		set_terminal("do");
		set_terminal("cr");
	}
}

void	find_prompt_y_heredoc(char *line)
{
	int i;

	i = g_21sh->cursor_heredoc.prompt_y + (ft_strlen("heredoc> ") + ft_strlen(line))
	 / g_21sh->window.ws_col;
	while (i-- > g_21sh->window.ws_row)
	{
		if (g_21sh->cursor_heredoc.prompt_y < 1)
			return ;
		g_21sh->cursor_heredoc.prompt_y--;
	}
}

void	cursor_jump_up_heredoc(char *line, int *left_len)
{
	int	text_len;
	int	chars_skipped;

	text_len = ft_strlen("heredoc> ") + ft_strlen(line);
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

void	move_cursor_heredoc(char *line)
{
	int len;

	len = g_21sh->cursor_heredoc.x;
	if ((ft_strlen("heredoc> ") + ft_strlen(line)) % g_21sh->window.ws_col == 0)
		move_cursor_next_line_heredoc(line);
	find_prompt_y_heredoc(line);
	cursor_jump_up_heredoc(line, &len);
	while (len++ < 0)
		set_terminal("le");
}

int		get_heredoc_input(char **line)
{
	char	previous_pressed_key;
	int		value;

	*line = ft_strnew(0);
	save_cursor_position_heredoc();
	while ((value = handle_keys_heredoc(line, &previous_pressed_key)) > 0)
	{
		//should not exit from child process, instead find some way to return 0 here
		if (input_too_large_heredoc(line))
			break;
		move_cursor_start_heredoc();
		set_terminal("cd");
		print_input_heredoc(*line);
		move_cursor_heredoc(*line);
	}
	if (value == -1)
		return (0);
	return (1);
}

void	redirect_heredoc_to_input(char *eof)
{
	char	*line;
	int		fd;


	//tcsetattr(STDOUT_FILENO, TCSAFLUSH, &g_21sh->raw);
	tcsetattr(g_21sh->stdout, TCSAFLUSH, &g_21sh->raw);

	g_21sh->cursor_heredoc.prompt_x = g_21sh->cursor_heredoc.prompt_x + 1;
	g_21sh->cursor_heredoc.prompt_y = g_21sh->cursor_heredoc.prompt_y + 1;
	//g_21sh->cursor_heredoc.x = ft_strlen("heredoc> ");
	//g_21sh->cursor_heredoc.y = g_21sh->cursor_heredoc.prompt_x;
	
	// open tmp file
	if ((fd = open(".heredoc.tmp", O_WRONLY | O_CREAT | O_TRUNC, 0666)) == -1)
		handle_error("Open failed", 1);
	
	ft_fprintf(g_21sh->stdout ,"heredoc> ");
	while (get_heredoc_input(&line))
	{
		if (ft_strequ(line, eof))
			break ;
		ft_putendl_fd(line, fd); // write to tmp file
		free(line);
		ft_fprintf(g_21sh->stdout, "\nheredoc> ");
	}
	free(line);
	ft_fprintf(g_21sh->stdout, "\n");

	close(fd);
	fd = open(".heredoc.tmp", O_RDONLY);
	close(STDIN_FILENO);
	dup2(fd, STDIN_FILENO);
}

int		string_is_number(char *str)
{
	int i;

	if (!str)
		return (0);
	while (str[i])
	{
		if (!ft_isdigit(str[i++]))
			return (0);
	}
	return (1);
}

void	check_file_descriptors_valid(char *word1, char *word2)
{
	if (word1 && !string_is_number(word1))
	{
		ft_fprintf(STDERR_FILENO, "%s: Bad file descriptor\n", word1);
		exit(1);
	}
	if (!string_is_number(word2) && !ft_strequ(word2, "-"))
	{
		ft_fprintf(STDERR_FILENO, "%s: Bad file descriptor\n", word1);
		exit(1);
	}
	if (((read(ft_atoi(word2), 0, 0) == -1) && (write(ft_atoi(word2), 0, 0))) && !ft_strequ(word2, "-"))
	{
		ft_fprintf(STDERR_FILENO, "%s: Bad file descriptor\n", word2);
		exit(1);
	}
	if (word1 && ((read(ft_atoi(word1), 0, 0) == -1) && (write(ft_atoi(word1), 0, 0))))
	{
		ft_fprintf(STDERR_FILENO, "%s: Bad file descriptor\n", word1);
		exit(1);
	}
}

void	redirect_fd_to_fd(char *word1, char *word2, int type)
{
	int fd1;
	int	fd2;

	//add defaults for >& and <&
	check_file_descriptors_valid(word1, word2);
	if (word1)
		fd1 = ft_atoi(word1);
	else
		fd1 = type == TOKEN_SMALER_ET ? STDIN_FILENO : STDOUT_FILENO;
	fd2 = ft_atoi(word2);
	close(fd1);
	if (!ft_strequ(word2, "-"))
		dup2(fd2, fd1);
}

void	handle_redirections(t_command *command)
{
	//open files for reading/writing, dup2 to change to appropriate fd
	t_redir *tmp;
	
	tmp = command->redirections;
	while (tmp)
	{
		if (tmp->type == TOKEN_LRGER)
			redirect_output_to_file_truncate(tmp->word);
		if (tmp->type == TOKEN_EXTRACTION)
			redirect_output_to_file_append(tmp->word);
		if (tmp->type == TOKEN_SMLER)
			redirect_file_to_input(tmp->word);
		if (tmp->type == TOKEN_INSERTION)
			redirect_heredoc_to_input(tmp->word);
		if (tmp->type == TOKEN_SMALER_ET || tmp->type == TOKEN_LRGER_ET) // <&, >&
			redirect_fd_to_fd(tmp->word, tmp->word2, tmp->type);	
		tmp = tmp->next;
	}
}

char	**command_arguments_to_arr(t_command *command)
{
	char	**args;
	t_arg	*tmp;
	size_t	i;
	
	i = 0;
	tmp = command->arguments;
	while (tmp)
	{
		tmp = tmp->next;
		i++;
	}
	if (!(args = (char**)ft_memalloc(sizeof(char*) * (i + 1))))
		handle_error("Malloc failed", 1);
	i = 0;
	tmp = command->arguments;
	while (tmp)
	{
		args[i++] = tmp->word;
		tmp = tmp->next;
	}
	return (args);
}

void	handle_binaries(char **args)
{
	char *filepath;

	if (!(filepath = find_filepath(args[0])))
	{
		print_error(ft_sprintf("Command not found: '%s'", args[0]));
		exit(1);
	}
	else
	{
		if (execve(filepath, args, g_21sh->envp) == -1)
			print_error(ft_sprintf("%s: Permission denied.", filepath));
	}
}

void	pipe_input(int *pipes, int command_num)
{
	dup2(pipes[(command_num - 1) * 2], STDIN_FILENO);
}

void	pipe_output(int *pipes, int command_num)
{
	dup2(pipes[command_num * 2 + 1], STDOUT_FILENO);
}

void	close_pipes(int *pipes)
{
	int i;

	i = 0;
	if (!pipes)
		return ;
	while (pipes[i] != -1)
		close(pipes[i++]);
}

void	child_execute_command(t_command *command, int *pipes, int command_num)
{
	char **args;

	if (pipes && command_num > 0)
		pipe_input(pipes, command_num);
	if (pipes && command->next)
		pipe_output(pipes, command_num);
	close_pipes(pipes);
	handle_redirections(command);
	// if (pipes)
	// 	close(pipes[command_num * 2 + 1]);

	args = command_arguments_to_arr(command);
	if (!handle_builtins(args)) // change to exit with proper builtin return values
		handle_binaries(args);
	if (pipes && command_num > 0)
		close(STDIN_FILENO);
	if (pipes && command->next)
		close(STDOUT_FILENO);
	exit(0);
}

void	execute_builtin_in_parent(t_command *command)
{
	char	**args;
	int		output_fd;
	int		error_fd;

	args = command_arguments_to_arr(command);
	output_fd = dup(STDOUT_FILENO);
	error_fd = dup(STDERR_FILENO);
	close(STDOUT_FILENO);
	close(STDERR_FILENO);
	handle_builtins(args);
	dup2(output_fd, STDOUT_FILENO);
	dup2(error_fd, STDERR_FILENO);
	close(output_fd);
	close(error_fd);
}

int	execute_command(t_command *command, int *pipes, int command_num)
{
	char	*filepath;
	pid_t	pid;

	tcsetattr(STDOUT_FILENO, TCSAFLUSH, &g_21sh->old); //set terminal to normal temporarily??

	if ((pid = fork()) == -1)
		handle_error("Error forking", 1);
	if (pid == 0)
		child_execute_command(command, pipes, command_num);
	else
	{
		execute_builtin_in_parent(command);
		if (pipes && command_num > 0)
			close(pipes[(command_num - 1) * 2]);
		if (pipes && command->next)
			close(pipes[command_num * 2 + 1]);
	}
	return (pid);
}

void	run_commands_group(t_command *commands)
{
	int			*pipes;
	int			command_num;
	int			amount;
	t_command	*tmp_command;
	int			*pids;

	pipes = get_pipes(commands);

	command_num = 0;
	amount = commands_amount(commands);
	if (!(pids = (int*)ft_memalloc(sizeof(int) * amount)))
		handle_error("Malloc failed", 1);
	tmp_command = commands;
	while (command_num < amount)
	{
		pids[command_num] = execute_command(tmp_command, pipes, command_num);
		command_num++;
		tmp_command = tmp_command->next;
	}
	command_num = 0;
	while (command_num < amount)
		wait_for_child(pids[command_num++]);
	tcsetattr(STDOUT_FILENO, TCSAFLUSH, &g_21sh->raw); //set terminal back to raw mode??
}

void	run_commands(void)
{
	t_command	*commands;

	while (g_21sh->token) // handle set of tokens at a time, split by ;
	{
		commands = get_commands();
		//print_commands(commands);
		if (g_21sh->token)
			g_21sh->token = g_21sh->token->next;
		run_commands_group(commands);
	}
}

void	move_cursor_newline()
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
	if (x > 1)
	{
		set_terminal(TEXT_INVERSE_VIDEO);
		ft_printf("%%");
		set_terminal(TEXT_NORMAL);
		ft_printf("\n");
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
		// while (current)
		// {
		// 	ft_printf("\ntoken: %d %s\n", current->type,current->value);
		// 	//ft_printf("\ntoken: *token: %p *value: %p prev:%p next:%p type: %d value:%s\n",current, current->value, current->prev, current->next, current->type, current->value);
		// 	current = current->next;
		// }
		ft_printf("\n");
		handle_expansion();
		run_commands();
		move_cursor_newline(); //if output didn't end with newline
		//check_cmd(); // write somekind of ast tree or grammar, then execute commands
		
		free_history();
		// free(commands);
		free(g_21sh->line);
		//set_terminal(SPECIAL_MODE); //what is this for??
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
