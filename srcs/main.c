/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwilen <jwilen@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/15 12:28:40 by sadawi            #+#    #+#             */
/*   Updated: 2021/03/01 13:53:28 by jwilen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"


void free_command(t_command *commands)
{
   t_command *tmp;

   while (commands)
    {
	   tmp = commands;
       commands = commands->next;
       free(tmp->arguments);
	   free(tmp);
    }

}

// void free_arg(t_arg *arg)
// {
//    t_arg *tmp;

//    while (arg)
//     {
       
// 	   tmp = arg;
//        arg = arg->next;
//     //    free(tmp->word);
// 	free(tmp);
	   
//     }

// }

void	init_key_sequences(void)
{
	char *sequence;

	sequence = tgetstr(LEFT_SEQUENCE, NULL);
	g_21sh->key_sequences.left_arrow = ft_strlen(sequence) > 2 ?
	sequence[2] : 0;
	sequence = tgetstr(RIGHT_SEQUENCE, NULL);
	g_21sh->key_sequences.right_arrow = ft_strlen(sequence) > 2 ?
	sequence[2] : 0;
	sequence = tgetstr(UP_SEQUENCE, NULL);
	g_21sh->key_sequences.up_arrow = ft_strlen(sequence) > 2 ?
	sequence[2] : 0;
	sequence = tgetstr(DOWN_SEQUENCE, NULL);
	g_21sh->key_sequences.down_arrow = ft_strlen(sequence) > 2 ?
	sequence[2] : 0;
	sequence = tgetstr(DELETE_SEQUENCE, NULL);
	g_21sh->key_sequences.delete_key = ft_strlen(sequence) > 2 ?
	sequence[2] : 0;
}

int		main(int argc, char **argv, char *envp[])
{
	(void)(argc && argv);
	g_debug = (argc > 1); // ENABLE DEBUGGING, DISABLES TERMCAPS
	if (!(g_21sh = (t_21sh*)ft_memalloc(sizeof(t_21sh))))
		handle_error("Malloc failed", 1);
	g_21sh->stdin = dup(STDIN_FILENO);
	g_21sh->stdout = dup(STDOUT_FILENO);
	g_21sh->copy_start = -1;
	g_debug ? 0 : init_termcaps(); // DEBUGGING
	init_signal_handling();
	g_debug ? 0 : create_terminal_raw_mode(); // DEBUGGING
	g_debug ? 0 : set_terminal_raw_mode(); // DEBUGGING
	init_env(envp);
	g_debug ? 0 : clear_screen(); // DEBUGGING
	loop_shell();
	restore_terminal_mode();
	return (0);
}
