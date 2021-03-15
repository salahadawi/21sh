/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flag_suwxz.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwilen <jwilen@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/15 09:06:43 by jwilen            #+#    #+#             */
/*   Updated: 2021/03/15 09:07:10 by jwilen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test.h"

int				flag_s_test(char *path)
{
	struct stat		buf;

	if (stat(path, &buf) == -1)
		return (1);
	return (!(buf.st_size > 0));
}

int				flag_u_test(char *path)
{
	struct stat		buf;

	if (stat(path, &buf) == -1)
		return (1);
	return (!(buf.st_mode & S_ISUID));
}

int				flag_w_test(char *path)
{
	if (access(path, W_OK) == 0)
		return (0);
	return (1);
}

int				flag_x_test(char *path)
{
	if (access(path, X_OK) == 0)
		return (0);
	return (1);
}

int				flag_z_test(char *path)
{
	if (path && !path[0])
		return (0);
	return (1);
}
