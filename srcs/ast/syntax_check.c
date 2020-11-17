/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_check.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwilen <jwilen@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/17 17:17:40 by jwilen            #+#    #+#             */
/*   Updated: 2020/11/17 18:22:20 by jwilen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

int			check_syntax(t_token *token)
{
	t_token		*current;
	int			stack[4096];
	int			i;
	int			len;

	i = 0;
	len = 0;
	stack[i] = 0;
	current = token;
	while (current->next != NULL)
	{
		stack[++i] = current->type;
		len++;
		current = current->next;
	}
	i= 1;
	while (i <= len)
	{
		ft_printf("\nstack[%d] = %d\n", i, stack[i]);
		i++;
	}
	write(1, " OP ", 4);
	return (0);
}