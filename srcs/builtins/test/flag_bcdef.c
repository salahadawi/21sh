/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flag_bcdef.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwilen <jwilen@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/15 08:59:47 by jwilen            #+#    #+#             */
/*   Updated: 2021/03/15 09:00:17 by jwilen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test.h"

int				flag_b_test(char *path)
{
	struct stat		buf;

	if (stat(path, &buf) == -1)
		return (1);
	return (!((buf.st_mode & S_IFMT) == S_IFBLK));
}

int				flag_c_test(char *path)
{
	struct stat		buf;

	if (stat(path, &buf) == -1)
		return (1);
	return (!((buf.st_mode & S_IFMT) == S_IFCHR));
}

int				flag_d_test(char *path)
{
	struct stat		buf;

	if (stat(path, &buf) == -1)
		return (1);
	return (!((buf.st_mode & S_IFMT) == S_IFDIR));
}

int				flag_e_test(char *path)
{
	if (access(path, F_OK) == 0)
		return (0);
	return (1);
}

int				flag_f_test(char *path)
{
	struct stat		buf;

	if (stat(path, &buf) == -1)
		return (1);
	return (!((buf.st_mode & S_IFMT) == S_IFREG));
}
