/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands_gamma.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwilen <jwilen@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/14 21:05:32 by jwilen            #+#    #+#             */
/*   Updated: 2021/02/24 10:40:43 by jwilen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

// is this a need function or just for debug??? - JWI
void	print_commands(t_command *commands)
{
	t_command	*tmp_command;
	t_arg		*tmp_arg;
	t_redir		*tmp_redir;
	int			i;

	i = 1;
	tmp_command = commands;
	while (tmp_command)
	{
		tmp_arg = tmp_command->arguments;
		tmp_redir = tmp_command->redirections;
		ft_printf("Command %d:\n", i++);
		if (tmp_arg)
			ft_printf("Arguments: ");
		while (tmp_arg)
		{
			ft_printf("%s ", tmp_arg->word);
			tmp_arg = tmp_arg->next;
		}
		if (tmp_redir)
			ft_printf("\nRedirections: ");
		while (tmp_redir)
		{
			ft_printf("Type: %s, File: %s ",
			token_type_to_char(tmp_redir->type), tmp_redir->word);
			tmp_redir = tmp_redir->next;
		}
		ft_printf("\n");
		tmp_command = tmp_command->next;
	}
	ft_printf("\n");
}

size_t	commands_amount(t_command *commands)
{
	t_command	*tmp;
	size_t		i;

	i = 0;
	tmp = commands;
	while (tmp)
	{
		tmp = tmp->next;
		i++;
	}
	return (i);
}

int		string_is_number(char *str)
{
	int i;

	i = 0;
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

	/*
	** add defaults for >& and <&
	*/
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
