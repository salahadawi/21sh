/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sadawi <sadawi@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/17 14:23:12 by sadawi            #+#    #+#             */
/*   Updated: 2021/02/03 20:58:34 by sadawi           ###   ########.fr       */
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

void	add_redir(t_command *command)
{
	static t_redir *cur_redir;

	if (!command->redirections)
	{
		cur_redir = new_redir();
		command->redirections = cur_redir;
	}
	else
	{
		cur_redir->next = new_redir();
		cur_redir = cur_redir->next;
	}
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
		if (check_token_redir())
			add_redir(command);
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
	pipes = (int*)ft_memalloc(sizeof(int) * pipe_amount);
	i = 0;
	while (i < pipe_amount)
	{
		pipe(&(pipes[i]));
		i += 2;
	}
	return (pipes);
}

void	redirect_output_to_file_truncate(char *file)
{
	int fd;

	fd = open(file, O_TRUNC | O_WRONLY | O_CREAT);
	close(STDOUT_FILENO);
	dup2(fd, STDOUT_FILENO);
}

void	redirect_output_to_file_append(char *file)
{
	int fd;

	fd = open(file, O_APPEND | O_WRONLY | O_CREAT);
	close(STDOUT_FILENO);
	dup2(fd, STDOUT_FILENO);
}

void	redirect_file_to_input(char *file)
{
	int fd;

	fd = open(file, O_RDONLY);
	close(STDIN_FILENO);
	dup2(fd, STDIN_FILENO);
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


void	child_execute_command(t_command *command, int *pipes, int command_num)
{
	char **args;

	if (pipes && command_num > 0)
		pipe_input(pipes, command_num);
	if (pipes && command->next)
		pipe_output(pipes, command_num);
	// if (pipes)
	// 	close(pipes[command_num * 2 + 1]);
	handle_redirections(command);
	
	args = command_arguments_to_arr(command);
	if (!handle_builtins(args)) // change to exit with proper builtin return values
		handle_binaries(args);
	if (pipes && command_num > 0)
		close(STDIN_FILENO);
	if (pipes && command->next)
		close(STDOUT_FILENO);
	exit(0);
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
		run_commands();
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
