/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_command.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sadawi <sadawi@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/17 14:18:58 by sadawi            #+#    #+#             */
/*   Updated: 2020/04/17 14:19:36 by sadawi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		exec_cmd(t_env *env, char **args)
{
	char	*filepath;
	pid_t	pid;

	pid = fork();
	if (pid == 0)
	{
		if (!(filepath = find_filepath(env, args[0])))
		{
			print_error(ft_sprintf("Command not found: '%s'", args[0]));
			free(filepath);
			exit(1);
		}
		else
		{
			if (execve(filepath, args, env->envp) == -1)
				print_error(ft_sprintf("%s: Permission denied.", filepath));
		}
	}
	else if (pid < 0)
		print_error(ft_sprintf("Error forking"));
	else
		wait_for_child(pid);
	return (1);
}

char	*find_filepath(t_env *env, char *filename)
{
	char	*filepath;
	char	**paths;
	int		filename_len;
	int		i;

	paths = ft_strsplit(get_env_value(env, "PATH"), ':');
	filename_len = ft_strlen(filename);
	i = 0;
	if (access(filename, F_OK) != -1)
		return (filename);
	if (!paths)
		return (NULL);
	while (paths[i])
	{
		filepath = create_filepath(paths[i], filename, filename_len);
		if (access(filepath, F_OK) != -1)
			return (filepath);
		free(paths[i]);
		free(filepath);
		i++;
	}
	free(paths);
	return (NULL);
}

char	*create_filepath(char *path, char *filename, int len)
{
	char *filepath;

	filepath = (char*)ft_memalloc(ft_strlen(path) + len + 2);
	ft_strcpy(filepath, path);
	ft_strcat(filepath, "/");
	ft_strcat(filepath, filename);
	return (filepath);
}

void	wait_for_child(pid_t pid)
{
	int status;

	waitpid(pid, &status, WUNTRACED);
	while (!WIFEXITED(status) && !WIFSIGNALED(status))
		waitpid(pid, &status, WUNTRACED);
}
