/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sadawi <sadawi@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/12 16:07:17 by jwilen            #+#    #+#             */
/*   Updated: 2021/03/11 21:06:35 by sadawi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

t_command		*get_next_command(void)
{
	t_command	*command;

	if (!g_21sh->token || g_21sh->token->type == TOKEN_SEMI
	|| g_21sh->token->type == TOKEN_BACKGROUND)
		return (NULL);
	if (!(command = (t_command*)ft_memalloc(sizeof(t_command))))
		handle_error("Malloc failed", 1);
	while (g_21sh->token && g_21sh->token->type != TOKEN_PIPE &&
	g_21sh->token->type != TOKEN_SEMI)
	{
		if (check_token_fd_aggregation())
			add_redir(command, AGGREGATION);
		else if (check_token_redir())
			add_redir(command, NO_AGGREGATION);
		else if (g_21sh->token->type == TOKEN_BACKGROUND)
		{
			command->background = 1;
			break ;
		}
		else
			add_arg(command);
		
	}
	if (g_21sh->token && g_21sh->token->type == TOKEN_PIPE)
		advance_tokens();
	return (command);
}

t_command		*get_commands(void)
{
	t_command	*commands;
	t_command	*tmp;
	int			command_num;

	commands = NULL;
	command_num = 0;
	while (1)
	{
		if (!commands)
		{
			tmp = get_next_command();
			commands = tmp;
			if (commands)
				commands->num = command_num++;
		}
		else
		{
			tmp->next = get_next_command();
			tmp = tmp->next;
			if (tmp)
				tmp->num = command_num++;
		}
		if (!tmp)
			break ;
	}
	return (commands);
}

void			run_commands_group(t_command *commands)
{
	int			*pipes;
	int			command_num;
	int			amount;
	t_command	*tmp_command;
	int			*pids;

	pipes = get_pipes(commands);
	command_num = 0;
	amount = commands_amount(commands);
	if (!(pids = (int*)ft_memalloc(sizeof(int) * amount)))
		handle_error("Malloc failed", 1);
	tmp_command = commands;
	while (command_num < amount)
	{
		pids[command_num] = execute_command(tmp_command, pipes, tmp_command->num);
		command_num++;
		tmp_command = tmp_command->next;
	}
	command_num = 0;
	while (command_num < amount)
		wait_for_child(pids[command_num++]);
	tcsetattr(STDOUT_FILENO, TCSAFLUSH, &g_21sh->raw); //set terminal back to raw mode??
	//jwi
	free (pids);
	free(pipes);
}

t_job			*create_job(t_command *commands)
{
	t_job *job;

	if (!(job = (t_job*)ft_memalloc(sizeof(t_job))))
		handle_error("Malloc failed", 1);
	job->pipes = get_pipes(commands);
	return (job);
}

t_process	*create_process(t_command *command)
{
	t_process *process;

	if (!(process = (t_process*)ft_memalloc(sizeof(t_process))))
		handle_error("Malloc failed", 1);
	process->command = command;
	return (process);
}

void	save_job(t_job *job)
{
	t_job *tmp;

	if (!g_21sh->jobs)
		g_21sh->jobs = job;
	else
	{
		tmp = g_21sh->jobs;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = job;
	}
}

void			format_job_info(t_job *job, char *status)
{
	ft_fprintf(STDERR_FILENO, "%ld (%s)\n", (long)job->pgid, status);
}

void launch_process(t_job *job, t_process *process)
{
	pid_t	pid;
	char	**args;

	/* Put the process into the process group and give the process group
         the terminal, if appropriate.
         This has to be done both by the shell and in the individual
         child processes because of potential race conditions.  */
	pid = getpid();
	if (job->pgid == 0)
		job->pgid = pid;
	setpgid(pid, job->pgid);
	if (job->ground)
		ft_tcsetpgrp(STDIN_FILENO, job->pgid);

	/* Set the handling for job control signals back to the default.  */
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	signal(SIGTSTP, SIG_DFL);
	signal(SIGTTIN, SIG_DFL);
	signal(SIGTTOU, SIG_DFL);
	signal(SIGCHLD, SIG_DFL);

	/* Exec the new process.  Make sure we exit.  */
	if (job->pipes && process->command->num > 0)
		pipe_input(job->pipes, process->command->num);
	if (job->pipes && process->command->next)
		pipe_output(job->pipes, process->command->num);
	close_pipes(job->pipes);
	handle_redirections(process->command); //should redirections happen before pipes?? example: ls >/dev/null | cat -e
	args = command_arguments_to_arr(process->command);
	if (!handle_builtins(args)) // change to exit with proper builtin return values // could get exit value from waitpid?
		handle_binaries(args);
	tcsetattr(STDOUT_FILENO, TCSAFLUSH, &g_21sh->raw);
	exit(1);
}

int			job_is_stopped(t_job *job)
{
	t_process *tmp;
	
	tmp = job->first_process;
	while (tmp)
	{
		if (!tmp->completed && !tmp->stopped)
			return (0);
		tmp = tmp->next;
	}
	return (1);
}

/* Return true if all processes in the job have completed.  */
int			job_is_completed(t_job *job)
{
	t_process *tmp;
	
	tmp = job->first_process;
	while (tmp)
	{
		if (!tmp->completed)
			return (0);
		tmp = tmp->next;
	}
	return (1);
}

int			mark_process_status(pid_t pid, int status)
{
	t_job		*tmp_job;
	t_process	*tmp_process;

	if (pid > 0)
	{
		/* Update the record for the process.  */
		tmp_job = g_21sh->jobs;
		while (tmp_job)
		{
			tmp_process = tmp_job->first_process;
			while (tmp_process)
			{
				if (tmp_process->pid == pid)
				{
					tmp_process->status = status;
					if (WIFSTOPPED(status))
						tmp_process->stopped = 1;
					else 
					{
						tmp_process->completed = 1;
						if (WIFSIGNALED(status))
							ft_fprintf(STDERR_FILENO, "%d: Terminated by signal %d.\n",
									(int)pid, WTERMSIG(tmp_process->status));
					}
					return (0);
				}
				tmp_process = tmp_process->next;
			}
			tmp_job = tmp_job->next;
		}
		ft_fprintf(STDERR_FILENO, "No child process %d.\n", pid);
		return (-1);
	}
	else if (pid == 0)
		/* No processes ready to report.  */
		return (-1);
	else
		return -1;
}

void		update_status(void)
{
	int		status;
	pid_t	pid;

	pid = waitpid (WAIT_ANY, &status, WUNTRACED|WNOHANG);
  	while (!mark_process_status (pid, status))
		pid = waitpid (WAIT_ANY, &status, WUNTRACED|WNOHANG);
}

void	free_job(t_job *job)
{
	t_process	*process;
	t_process	*next_process;

	process = job->first_process;
	while (process)
	{
		next_process = process->next;
		free_command(process->command);
		free(process);
		process = next_process;
	}
	free(job->pipes);
	free(job);
}

void		do_job_notification(void)
{
	t_job	*job;
	t_job	*prev;
	t_job	*next;

  /* Update status information for child processes.  */
	update_status ();

	prev = NULL;
	job = g_21sh->jobs;
	while (job)
	{
		next = job->next;
		if (job_is_completed(job))
		{
			if (job->ground == BACKGROUND)
				format_job_info(job, "completed");
			if (prev)
				prev->next = job->next;
			else
				g_21sh->jobs = job->next;
			free_job(job);
		}
		else 
		{
			if (job_is_stopped(job) && !job->notified)
			{
				format_job_info(job, "stopped");
				job->notified = 1;
			}
			prev = job;
		}
		job = next;
	}
}

void	wait_for_job(t_job *job)
{
	int		status;
	pid_t	pid;

	while (1)
	{
		pid = waitpid(WAIT_ANY, &status, WUNTRACED);
		if (mark_process_status(pid, status) ||
			job_is_stopped(job) ||
			job_is_completed(job))
			break;
	}
}

void put_job_in_foreground(t_job *job, int cont)
{

	(void)cont;
	/* Put the job into the foreground.  */
	ft_tcsetpgrp(STDIN_FILENO, job->pgid);
	/* Send the job a continue signal, if necessary.  */
	if (cont)
	{
		tcsetattr(STDIN_FILENO, TCSADRAIN, &job->tmodes);
		if (kill(-job->pgid, SIGCONT) < 0)
			handle_error("kill (SIGCONT)", 0);
	}
	/* Wait for it to report.  */
	wait_for_job(job);

	/* Put the shell back in the foreground.  */
	ft_tcsetpgrp(STDIN_FILENO, g_21sh->shell_pgid);

	/* Restore the shell’s terminal modes.  */
	tcgetattr(STDIN_FILENO, &job->tmodes);
	tcsetattr(STDIN_FILENO, TCSADRAIN, &g_21sh->raw);
	//tcsetattr(STDIN_FILENO, TCSAFLUSH, &g_21sh->raw);
}

void put_job_in_background(t_job *job, int cont)
{
	(void)(job && cont);
	// /* Send the job a continue signal, if necessary.  */
	// if (cont)
	// 	if (kill(-j->pgid, SIGCONT) < 0)
	// 		perror("kill (SIGCONT)");
	tcsetattr(STDIN_FILENO, TCSADRAIN, &g_21sh->raw);
}

void 			launch_job(t_job *job)
{
	t_process *tmp;
	pid_t pid;

	tmp = job->first_process;
	while (tmp)
	{
		tcsetattr(STDIN_FILENO, TCSAFLUSH, &g_21sh->old);
		if ((pid = fork()) == -1)
			handle_error("Error forking", 1);
		if (pid == 0)
			launch_process(job, tmp);
		else
		{
			tmp->pid = pid;
			if (!job->pgid)
			{
				job->pgid = pid;
				setpgid(pid, job->pgid);
			}
			//execute_builtin_in_parent(tmp->command); //only if job in foreground?
			if (job->pipes && tmp->command->num > 0)
				close(job->pipes[(tmp->command->num - 1) * 2]);
			if (job->pipes && tmp->command->next)
				close(job->pipes[tmp->command->num * 2 + 1]);
		}
		tmp = tmp->next;
	}
	if (job->ground == BACKGROUND)
		format_job_info(job, "launched");
	if (job->ground == FOREGROUND)
		put_job_in_foreground(job, 0);
	else
		put_job_in_background(job, 0);
}

int		get_job_ground(t_command *commands)
{
	while (commands)
	{
		if (commands->background)
			return (BACKGROUND);
		commands = commands->next;
	}
	return (FOREGROUND);
}

void			handle_job(t_command *commands)
{
	t_job		*job;
	t_process	*process;

	job = create_job(commands);
	job->ground = get_job_ground(commands);
	while (commands)
	{
		if (!job->first_process)
		{
			process = create_process(commands);
			job->first_process = process;
		}
		else
		{
			process->next = create_process(commands);
			process = process->next;
		}
		commands = commands->next;
	}
	save_job(job);
	launch_job(job);
}

void			run_commands(void)
{
	t_command	*commands;

/*
** handle set of tokens at a time, split by ;
*/
	while (g_21sh->token)
	{
		commands = get_commands();
		if (g_21sh->token)
			advance_tokens();
		//print_commands(commands);
		//run_commands_group(commands);
		if (commands)
			handle_job(commands);
		//free_command(commands); 	// jwi //should not free before a job is done
	}
	
}
