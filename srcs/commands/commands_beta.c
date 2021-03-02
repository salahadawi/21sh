/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands_beta.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwilen <jwilen@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/14 21:01:26 by jwilen            #+#    #+#             */
/*   Updated: 2021/03/02 20:12:41 by jwilen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

void	handle_redirections(t_command *command)
{
	/*
	** open files for reading/writing, dup2 to change to appropriate fd
	*/
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
		if (tmp->type == TOKEN_SMALER_ET || tmp->type == TOKEN_LRGER_ET)
			redirect_fd_to_fd(tmp->word, tmp->word2, tmp->type);
		tmp = tmp->next;
	}
}

void	handle_binaries(char **args)
{
	char *filepath;

	if (!(filepath = find_filepath(args[0])) || (access(filepath, X_OK) != 0))
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
