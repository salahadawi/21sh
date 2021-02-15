/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwilen <jwilen@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/17 14:23:12 by sadawi            #+#    #+#             */
/*   Updated: 2021/02/15 14:31:25 by jwilen           ###   ########.fr       */
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
	run_first();
	return (0);
}
