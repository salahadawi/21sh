/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sadawi <sadawi@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/17 14:23:12 by sadawi            #+#    #+#             */
/*   Updated: 2020/04/17 14:23:35 by sadawi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	loop_shell(t_env *env)
{
	char	**commands;
	char	*line;
	char	**args;
	int		loop;
	int		i;

	loop = 1;
	while (loop)
	{
		print_shell_info(env);
		if (get_next_line(0, &line) < 1)
			break ;
		commands = split_line_commands(line);
		i = 0;
		while (commands[i])
		{
			args = split_line_args(commands[i]);
			loop = check_cmd(env, args);
			free_args(args);
			free(commands[i++]);
		}
		free(commands);
		free(line);
	}
}

int		check_cmd(t_env *env, char **args)
{
	if (!args[0])
		return (1);
	handle_expansion(env, args);
	if (handle_builtins(env, args))
		return (1);
	return (exec_cmd(env, args));
}
