/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sadawi <sadawi@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/17 14:23:12 by sadawi            #+#    #+#             */
/*   Updated: 2020/04/30 13:25:50 by sadawi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

int		read_key(void)
{
	char c;
	char sequence[3];

	c = 0;
	if (read(STDOUT_FILENO, &c, 1) == -1)
		handle_error("Read failed", 1);
	if (c == ESCAPE)
	{
		if (read(STDOUT_FILENO, &sequence[0], 1) != 1)
			return (0);
		if (read(STDOUT_FILENO, &sequence[1], 1) != 1)
			return (0);
		if (sequence[0] == '[')
		{
			if (ft_isdigit(sequence[1]))
			{
				if (read(STDOUT_FILENO, &sequence[2], 1) != 1)
					return (0);
			}
			return (sequence[1] - 100);
		}
	}
	return (c);
}

void	handle_control_sequence(char *c)
{
	*c += 100;
	
	if (*c == g_21sh->key_sequences.delete)
	{
		
	}
	else if (*c == g_21sh->key_sequences.left_arrow)
		g_21sh->cursor.x--;
	else if (*c == g_21sh->key_sequences.right_arrow)
		g_21sh->cursor.x++;
	else if (*c == g_21sh->key_sequences.up_arrow)
		;
	else if (*c == g_21sh->key_sequences.down_arrow)
	{
			;
	}
}

int		handle_keys(char **line)
{
	char c;

	c = read_key();
	//ft_printf("%d", c);
	if (c == 0)
		return (1);
	if (c < 0)
	{
		handle_control_sequence(&c);
		return (1);
	}
	if (c == BACKSPACE)
	{

	}
	else if (c == ENTER)
		return (0);
	else if (c == 4)
		exit(0); //temporary, need to restore terminal and free memory here
	else
		*line = ft_strjoinfree(*line, ft_chartostr(c));
	return (1);
}

void	move_cursor_start(void)
{
	int len;

	len = g_21sh->prompt_len;
	set_terminal("cr");
	while (len-- > 0)
		set_terminal("nd");
}

void	move_cursor(void)
{
	int len;

	len = g_21sh->cursor.x;
	while (len++ < 0)
		set_terminal("le");
}

int		get_input(char **line)
{
	*line = ft_strnew(0);
	while (handle_keys(line))
	{
		move_cursor_start();
		set_terminal("cd");
		ft_printf("%s", *line);
		move_cursor();
	}
	if (line[0] == 0)
		return (0);
	return (1);
}

void	loop_shell(void)
{
	char	**commands;
	char	*line;
	char	**args;
	int		loop;
	int		i;

	loop = 1;
	while (loop)
	{
		g_21sh->cursor.x = 0;
		print_shell_info();
		if (get_input(&line) < 1)
			break ;
		ft_printf("\n");
		commands = split_line_commands(line);
		i = 0;
		while (commands[i])
		{
			args = split_line_args(commands[i]);
			loop = check_cmd(args);
			free_args(args);
			free(commands[i++]);
		}
		free(commands);
		free(line);
	}
}

int		check_cmd(char **args)
{
	if (!args[0])
		return (1);
	handle_expansion(args);
	if (handle_builtins(args))
		return (1);
	return (exec_cmd(args));
}
