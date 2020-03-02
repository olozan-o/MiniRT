/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct_fts.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olozano- <olozano-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/02 15:38:00 by olozano-          #+#    #+#             */
/*   Updated: 2020/03/02 17:06:54 by olozano-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

rt_objs		*push_new_object(rt_objs **begin_list)
{
	rt_objs	*new_one;

	if (!(new_one = malloc(sizeof(rt_objs))))
		return (NULL);
	new_one->coord = ft_calloc(3, sizeof(double));
	new_one->orient = ft_calloc(3, sizeof(double));
	new_one->params = ft_calloc(3, sizeof(double));
	new_one->color = ft_calloc(3, sizeof(double));
	new_one->next = *begin_list;
	*begin_list = new_one;
	return (new_one);
}

int			get_some_d(double *things, int how_many, char *where_from)
{
	int	i;
	int	*str_backup;

	i = 0;
	str_backup = where_from;
	while (i < how_many)
	{
		things[i] = ft_strtod(where_from);
		where_from = where_from + advance_through(where_from);
		i++;
		if (where_from != ',' && i < how_many)
			things[i - 1] = -43434343;
		where_from++;
	}
	if (*where_from == ' ' || *where_from == '\n')
		return (where_from - str_backup);
	else
	{
		return (0);
}
