/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_type.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwilen <jwilen@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/17 10:41:38 by jwilen            #+#    #+#             */
/*   Updated: 2021/03/20 07:49:51 by jwilen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"
#include "hash.h"

static int			check_builtin(char *args)
{
	int			j;
	t_builtins	*tmp;

	tmp = &g_21sh->builtins;
	j = 0;
	while (tmp->names[j])
	{
		if (!ft_strcmp(args, tmp->names[j]))
			return (1);
		j++;
	}
	return (0);
}

static void			print_path_case(char *arg, char **path)
{
	ft_fprintf(2, "%s is %s\n", arg, *path);
	ft_strdel(path);
}

static char			*check_path(char *arg)
{
	char		**paths;
	char		*path;

	paths = get_paths();
	if ((path = find_path(arg, paths)))
		return (path);
	return (NULL);
}

static void			print_res(char *arg)
{
	char *path;

	if (check_builtin(arg))
		ft_fprintf(STDOUT_FILENO, "%s is a shell builtin\n", arg);
	else if ((path = check_map(arg, g_21sh->hashmap, hash_check)))
		ft_fprintf(2, "%s is hashed (%s)\n", arg, path);
	else if ((path = check_path(arg)))
		print_path_case(arg, &path);
	else
		ft_fprintf(2, "42sh: type: %s: not found\n", arg);
}

int					builtin_type(char **args)
{
	size_t	i;
	size_t	d;

	d = 0;
	i = 0;
	if (!args[1])
		return (0);
	while (args[i])
		i++;
	d = i;
	i = 1;
	while (i < d)
	{
		print_res(args[i]);
		i++;
	}
	return (1);
}
