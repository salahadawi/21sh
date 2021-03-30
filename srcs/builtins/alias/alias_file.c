/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alias_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwilen <jwilen@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/22 08:15:30 by jwilen            #+#    #+#             */
/*   Updated: 2021/03/29 15:14:15 by jwilen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

void		free_alias(void)
{
	t_alias *tmp;

	if (!g_21sh->alias)
		return ;
	while (g_21sh->alias)
	{
		tmp = g_21sh->alias->next;
		free(g_21sh->alias->real_name);
		free(g_21sh->alias->alias_name);
		free(g_21sh->alias);
		g_21sh->alias = tmp;
	}
}

void		free_alias_node(t_alias **head_ref, t_alias *del)
{
	 /* base case */
    if (*head_ref == NULL || del == NULL)
        return;
 
    /* If node to be deleted is head node */
    if (*head_ref == del)
        *head_ref = del->next;
 
    /* Change next only if node to be deleted is NOT the last node */
    if (del->next != NULL)
        del->next->prev = del->prev;
 
    /* Change prev only if node to be deleted is NOT the first node */
    if (del->prev != NULL)
        del->prev->next = del->next;
 
    /* Finally, free the memory occupied by del*/
    free(del);
    return;
}

char		*produce_back_front(char **line, int i, size_t len, size_t len2)
{
	char	*back;
	char	*front;
	// ft_printf("LINE: %s\n", line[0]);
	// ft_printf("LINE1: %s\n", line[1]);
	front = NULL;
	// ft_printf("len: %d len2: %d\n", len, len2);
	if (i == 1)
	{
		back = (char*)malloc((sizeof(char) * (len2 - len)));
		// if (!(back = (char*)ft_memalloc(len2 - len))
		//     handle_error("Malloc failed", 1);
		ft_bzero(back, (len2));
		line[1] ? ft_strncpy(back, line[1], (ft_strlen(line[1]))) :
		ft_strncpy(back, *line + len, (len2-len));
		return (back);
	}
	else		
	{
		front = (char*)malloc((len) * sizeof(char));
		ft_bzero(front, len);
		ft_strncpy(front, *line, (len -1));
		return (front);
	}
	return (NULL);
}

t_alias		*new_alias_node(char **line, t_alias *prev)
{
	t_alias *node;
	size_t	len;
	size_t	len2;
	char	*front;
	char	*back;
	int		j = 0;

	len2 = 0;
	len = len_eql(line[0]);
	while (line[j])
	{
		len2 +=ft_strlen(line[j]);
		j++;
	}
	back = NULL;
	front = NULL;
	if (len2 > 0)
	{
		front = produce_back_front(line, 0, len, len2);
		back = produce_back_front(line, 1, len, len2);
		// ft_printf("FRONT2: %s\n", front);
		// ft_printf("BACK2: %s\n", back);
		
	}
	if (!(node = (t_alias*)ft_memalloc(sizeof(t_alias))))
		handle_error("Malloc failed", 1);
	node->alias_name = ft_strdup(front);
    node->real_name = ft_strdup(back);
	node->prev = prev;
	node->next = NULL;
	return (node);
}

void		add_to_alias(char **line)
{
	t_alias	*current;

	current = g_21sh->alias;
	if (!g_21sh->alias)
		g_21sh->alias = new_alias_node(line, NULL);
	else
	{
		while (current->next)
			current = current->next;
		current->next = new_alias_node(line, current);
		current = current->next;
	}
}
