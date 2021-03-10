/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   job_control.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sadawi <sadawi@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/08 16:39:07 by sadawi            #+#    #+#             */
/*   Updated: 2021/03/09 20:47:45 by sadawi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef JOB_CONTROL_H
# define JOB_CONTROL_H

# include "sh.h"

# define BACKGROUND 0
# define FOREGROUND 1

typedef struct			s_process
{
	struct s_process	*next;       /* next process in pipeline */
	t_command			*command;                /* for exec */
	pid_t				pid;                  /* process ID */
	char				completed;             /* true if process has completed */
	char				stopped;               /* true if process has stopped */
	int					status;                 /* reported status value */
}						t_process;

typedef struct		s_job
{
	struct s_job	*next;           /* next active job */
	t_process		*first_process;     /* list of processes in this job */
	pid_t			pgid;                 /* process group ID */
	char			notified;              /* true if user told about stopped job */
	struct termios	tmodes;      /* saved terminal modes */
	int				*pipes;
	int				ground;
}					t_job;

pid_t		ft_tcgetpgrp(int fd);

void		ft_tcsetpgrp(int fd, pid_t prgp);

#endif