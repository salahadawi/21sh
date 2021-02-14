/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands_gamma.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwilen <jwilen@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/14 21:05:32 by jwilen            #+#    #+#             */
/*   Updated: 2021/02/14 21:13:10 by jwilen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

int		string_is_number(char *str)
{
	int i;

	if (!str)
		return (0);
	while (str[i])
	{
		if (!ft_isdigit(str[i++]))
			return (0);
	}
	return (1);
}

void	check_file_descriptors_valid(char *word1, char *word2)
{
	if (word1 && !string_is_number(word1))
	{
		ft_fprintf(STDERR_FILENO, "%s: Bad file descriptor\n", word1);
		exit(1);
	}
	if (!string_is_number(word2) && !ft_strequ(word2, "-"))
	{
		ft_fprintf(STDERR_FILENO, "%s: Bad file descriptor\n", word1);
		exit(1);
	}
	if (((read(ft_atoi(word2), 0, 0) == -1) && (write(ft_atoi(word2), 0, 0)))
	&& !ft_strequ(word2, "-"))
	{
		ft_fprintf(STDERR_FILENO, "%s: Bad file descriptor\n", word2);
		exit(1);
	}
	if (word1 && ((read(ft_atoi(word1), 0, 0) == -1) &&
	(write(ft_atoi(word1), 0, 0))))
	{
		ft_fprintf(STDERR_FILENO, "%s: Bad file descriptor\n", word1);
		exit(1);
	}
}

void	redirect_fd_to_fd(char *word1, char *word2, int type)
{
	int fd1;
	int	fd2;

	//add defaults for >& and <&
	check_file_descriptors_valid(word1, word2);
	if (word1)
		fd1 = ft_atoi(word1);
	else
		fd1 = type == TOKEN_SMALER_ET ? STDIN_FILENO : STDOUT_FILENO;
	fd2 = ft_atoi(word2);
	close(fd1);
	if (!ft_strequ(word2, "-"))
		dup2(fd2, fd1);
}
