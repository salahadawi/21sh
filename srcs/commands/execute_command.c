/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_command.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwilen <jwilen@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/17 14:18:58 by sadawi            #+#    #+#             */
/*   Updated: 2021/03/30 07:02:06 by jwilen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

int		exec_cmd(char **args)
{
	char	*filepath;
	pid_t	pid;

	pid = fork();
	tcsetattr(STDOUT_FILENO, TCSAFLUSH, &g_21sh->old);
	if (pid == 0)
	{
		if (!(filepath = find_filepath(args[0])))
		{
			print_error(ft_sprintf("Command not found: '%s'", args[0]));
			free(filepath);
			exit(1);
		}
		else
		{
			if (execve(filepath, args, g_21sh->envp) == -1)
				print_error(ft_sprintf("%s: Permission denied.", filepath));
		}
	}
	else if (pid < 0)
		print_error(ft_sprintf("Error forking"));
	else
		wait_for_child(pid);
	tcsetattr(STDOUT_FILENO, TCSAFLUSH, &g_21sh->raw);
	return (1);
}

char	*find_filepath(char *filename)
{
	char	*filepath;
	char	**paths;
	int		filename_len;
	int		i;

	filename_len = ft_strlen(filename);
	if (access(filename, F_OK) != -1)
		return (filename);
	paths = ft_strsplit(get_env_value("PATH"), ':');
	if (!paths)
		return (NULL);
	i = -1;
	while (paths[++i])
	{
		filepath = create_filepath(paths[i], filename, filename_len);
		if (access(filepath, F_OK) != -1)
		{
			free_paths(paths, i);
			return (filepath);
		}
		free(paths[i]);
		free(filepath);
	}
	free(paths);
	return (NULL);
}

char	*create_filepath(char *path, char *filename, int len)
{
	char *filepath;

	if (!(filepath = (char*)ft_memalloc(ft_strlen(path) + len + 2)))
		handle_error("Malloc failed", 1);
	ft_strcpy(filepath, path);
	ft_strcat(filepath, "/");
	ft_strcat(filepath, filename);
	return (filepath);
}

void	wait_for_child(pid_t pid)
{
	int status;

	restore_signals();
	signal(SIGINT, SIG_IGN);
	waitpid(pid, &status, WUNTRACED);
	// while (!WIFEXITED(status))
	// {
	// 	waitpid(pid, &status, WUNTRACED);
	// }
	init_signal_handling();
}
