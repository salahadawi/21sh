/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sadawi <sadawi@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/17 14:23:12 by sadawi            #+#    #+#             */
/*   Updated: 2020/04/29 13:15:46 by sadawi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

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
		print_shell_info();
		if (get_next_line(0, &line) < 1)
			break ;
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
