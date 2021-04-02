/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_job_control.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sadawi <sadawi@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/10 15:53:39 by sadawi            #+#    #+#             */
/*   Updated: 2021/03/14 23:07:25 by sadawi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

void print_redir(t_redir *redir) //causes leaks with print_commands, for debug purposes
{
	if (redir->word2)
	{
		ft_putstr(redir->word);
		ft_putstr(redir->type == TOKEN_ET_SMLER ? "<&" : ">&");
		ft_printf("%s ", redir->word2);
	}
	else
	{
		ft_putstr(redir->type == TOKEN_LRGER ? ">" : NULL);
		ft_putstr(redir->type == TOKEN_SMLER ? "<" : NULL);
		ft_putstr(redir->type == TOKEN_EXTRACTION ? ">>" : NULL);
		ft_putstr(redir->type == TOKEN_INSERTION ? "<<" : NULL);
		ft_printf(" %s ", redir->word);
	}
}

void	print_job_command(t_job *job)
{
	t_command	*command;
	t_arg		*arg;
	t_redir		*redir;

	command = job->first_process->command;
	while (command)
	{
		arg = command->arguments;
		redir = command->redirections;
		while (arg)
		{
			ft_printf("%s ", arg->word);
			arg = arg->next;
		}
		while (redir)
		{
			print_redir(redir);
			redir = redir->next;
		}
		if (command->next)
			ft_printf("| ");
		command = command->next;
	}
}

int		job_characters_check_stopped(t_job *job, int *arr)
{
	int i;
	int amount;

	i = 0;
	amount = 0;
	while (job->next && amount < 2)
	{
		if (job->first_process->stopped)
			arr[i] = !amount++ ? 2 : 1;
		i++;
		job = job->next;
	}
	return (amount);
}

int		*get_job_character_array(t_job *job)
{
	int		*arr;
	int		size;
	int		amount;
	t_job	*tmp;

	size = 0;
	tmp = job;
	while (tmp->next)
	{
		size++;
		tmp = tmp->next;
	}
	if (!(arr = (int*)ft_memalloc(sizeof(int) * (size + 1))))
		handle_error("Malloc failed", 1);
	arr[size] = -1;
	tmp = job;
	amount = job_characters_check_stopped(job, arr);
	while (amount < 2 && size)
	{
		if (!arr[size - 1])
			arr[size - 1] = !amount++ ? 2 : 1;
			amount++;
		size--;
	}
	return (arr);
}

char	get_job_character(t_job *job, int job_num)
{
	char	character;
	int		*arr;

	arr = get_job_character_array(job);
	if (arr[job_num - 1])
		character = arr[job_num - 1] == 2 ? '+' : '-';
	else
		character = ' ';
	free(arr);
	return (character);
}

char	get_job_character2(t_job *job, int job_num)
{
	int	size;
	int	amount;
	int	i;
	t_job *tmp;

	size = 0;
	tmp = job;
	while (tmp->next)
	{
		size++;
		tmp = tmp->next;
	}
	tmp = job;
	amount = 0;
	i = 0;
	while (tmp->next && amount < 2)
	{
		if (tmp->first_process->stopped)
		{
			if (i + 1 == job_num)
				return (amount ? '-' : '+');
			amount++;
		}
		i++;
		tmp = tmp->next;
	}
	if (amount > 1)
		return (' ');
	else if (job_num == size)
		return (amount ? '-' : '+');
	else if (job_num == size - 1)
		return (amount ? ' ' : '-');
	return (' ');
}

int		builtin_jobs(char **args)
{
	t_job		*job;
	int			job_num;

	(void)args;
	job = g_21sh->jobs;
	job_num = 1;
	while (job->next)
	{
		ft_printf("[%d] %c %s ", job_num, get_job_character(g_21sh->jobs, job_num),
		job->first_process->stopped ? "suspended" : "running");
		print_job_command(job);
		ft_putchar('\n');
		job = job->next;
		job_num++;
	}
	return (0); //change all builtins to return 0 show they don't show up as stopped
}

void mark_job_as_running(t_job *job)
{
	t_process *process;

	process = job->first_process;
	while (process)
	{
		process->stopped = 0;
		process = process->next;
	}
	job->notified = 0;
}

t_job	*get_most_recent_job(void)
{
	int		i;
	int		*arr;
	t_job	*job;

	arr = get_job_character_array(g_21sh->jobs);
	i = 0;
	while (arr[i] != -1 && arr[i] != 2)
		i++;
	job = g_21sh->jobs;
	while (i--)
		job = job->next;
	return (job);
}

t_job	*get_job(char **args)
{
	t_job *job;

	job = g_21sh->jobs;
	if (!args[1] || ft_strequ(args[1], "%"))
	{
		return (get_most_recent_job());
	}
	return (t_job*)NULL;
}


int		builtin_fg(char **args) //Don't execute in child?
{
	t_job *job;

	job = get_job(args);
	if (!job)
		return (1);
	mark_job_as_running(job);
	ft_printf("%d\n", job->pgid);
	put_job_in_foreground(job, 1);
	return (0);
}

int		builtin_bg(char **args)
{
	t_job *job;

	job = get_job(args);
	mark_job_as_running(job);
	put_job_in_background(job, 1);
	return (1);
}