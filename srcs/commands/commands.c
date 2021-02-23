/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwilen <jwilen@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/12 16:07:17 by jwilen            #+#    #+#             */
/*   Updated: 2021/02/23 13:26:36 by jwilen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

t_command		*get_next_command(void)
{
	t_command	*command;
	// t_redir		*cur_redir;
	// t_arg		*cur_arg;

	if (!g_21sh->token || g_21sh->token->type == TOKEN_SEMI)
		return (NULL);
	if (!(command = (t_command*)ft_memalloc(sizeof(t_command))))
		handle_error("Malloc failed", 1);
	while (g_21sh->token && g_21sh->token->type != TOKEN_PIPE &&
	g_21sh->token->type != TOKEN_SEMI)
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

t_command		*get_commands(void)
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

void			run_commands_group(t_command *commands)
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

void			run_commands(void)
{
	t_command	*commands;

// handle set of tokens at a time, split by ;
	while (g_21sh->token)
	{
		commands = get_commands();
		//print_commands(commands);
		if (g_21sh->token)
			g_21sh->token = g_21sh->token->next;
		run_commands_group(commands);
	}
}
