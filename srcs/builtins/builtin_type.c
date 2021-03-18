/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_type.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwilen <jwilen@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/17 10:41:38 by jwilen            #+#    #+#             */
/*   Updated: 2021/03/18 08:50:11 by jwilen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"
#include "hash.h"

static void			print_type_error(const char *arg)
{
	ft_fprintf(2, "42sh");
	ft_fprintf(2, ": type: %s: not found\n", arg);
}

static int check_builtin(char *args)
{
	int	j;
	t_builtins	*tmp;

	tmp = &g_21sh->builtins;
	j = 0;
	while(tmp->names[j])
	{
		if (ft_strcmp(args, tmp->names[j]))
			return (1);
		j++;
	}
	return (0);
}

int			builtin_type(char **args)
{
	size_t	i;
	int		ret;
	// char	*path;

	ret = 0;
	i = 0;
	if (!args[1])
		return (0);
	while (args[++i])
	{
		if (check_builtin(args[i]))
			ft_fprintf(STDOUT_FILENO, "%s is a shell builtin\n", args[i]);
		// else if ((path = check_map(args[i], g_21sh->hashmap, hash_check)))
		// 	ft_fprintf(STDOUT_FILENO, "%s is a hashed (%s)\n", args[i], path);
		else
		{
			print_type_error(args[i]);
			ret = 1;
		}
		i++;
	}
	write(1, "END", 3);
	return (1);
}