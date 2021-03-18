/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands_alfa.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwilen <jwilen@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/14 20:52:48 by jwilen            #+#    #+#             */
/*   Updated: 2021/03/18 08:25:07 by jwilen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

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
	free(args);
	dup2(output_fd, STDOUT_FILENO);
	dup2(error_fd, STDERR_FILENO);
	close(output_fd);
	close(error_fd);
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
	args = command_arguments_to_arr(command);
	if (!handle_builtins(args))
		handle_binaries(args);
	exit(0);
}

int		execute_command(t_command *command, int *pipes, int command_num)
{
	pid_t	pid;

	tcsetattr(STDOUT_FILENO, TCSAFLUSH, &g_21sh->old);
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
