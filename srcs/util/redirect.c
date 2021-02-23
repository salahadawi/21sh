/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwilen <jwilen@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/18 08:49:44 by jwilen            #+#    #+#             */
/*   Updated: 2021/02/23 11:50:33 by jwilen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

void	redirect_output_to_file_truncate(char *file)
{
	int fd;

	fd = open(file, O_TRUNC | O_RDWR | O_CREAT, 0666);
	close(STDOUT_FILENO);
	dup2(fd, STDOUT_FILENO);
}

void	redirect_output_to_file_append(char *file)
{
	int fd;

	fd = open(file, O_APPEND | O_RDWR | O_CREAT, 0666);
	close(STDOUT_FILENO);
	dup2(fd, STDOUT_FILENO);
}

void	redirect_file_to_input(char *file)
{
	int fd;

	if ((fd = open(file, O_RDWR)) == -1)
	{
		ft_fprintf(STDERR_FILENO, "No such file or directory: %s\n", file);
		exit(1);
	}
	close(STDIN_FILENO);
	dup2(fd, STDIN_FILENO);
}
