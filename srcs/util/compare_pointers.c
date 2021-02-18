/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   compare_pointers.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sadawi <sadawi@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/17 14:22:17 by sadawi            #+#    #+#             */
/*   Updated: 2020/04/29 12:49:01 by sadawi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

int		find_size_pointers(char *str, char *ptr)
{
	int i;

	i = 0;
	while (str[i])
	{
		if (str[i] == *ptr)
			return (i);
		i++;
	}
	return (-1);
}
