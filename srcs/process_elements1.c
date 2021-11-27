/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_elements1.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olozano- <olozano-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/15 19:29:11 by olozano-          #+#    #+#             */
/*   Updated: 2021/11/27 10:38:57 by olozano-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

char	*process_cylinder(char *begin, rt_objs *ob)
{
	char	*it;

	it = get_some_d(ob->orient, 3, begin);
	if (!it)
		return (NULL);
	it = get_some_d(ob->params, 2, it);
	if (!it)
		return (NULL);
	it = get_some_d(ob->color, 3, it);
	if (!it)
		return (NULL);
	return (it);
}

char	*process_plane(char *begin, rt_objs *ob)
{
	char	*it;

	it = get_some_d(ob->orient, 3, begin);
	if (!it)
		return (NULL);
	it = get_some_d(ob->color, 3, it);
	if (!it)
		return (NULL);
	return (it);
}

char	*process_sphere(char *begin, rt_objs *ob)
{
	char	*it;

	it = get_some_d(ob->params, 1, begin);
	if (!it)
		return (NULL);
	it = get_some_d(ob->color, 3, it);
	if (!it)
		return (NULL);
	return (it);
}

int	process_object(rt_scene *sc, char *begin)
{
	char	*it;
	rt_objs	*ob;
	int		aux;

	if ((ft_strncmp(begin, "sp", 2) && ft_strncmp(begin, "pl", 2)
			&& ft_strncmp(begin, "cy", 2)) || !ft_isspace(begin[2]))
		exit_program("ERROR: unknown element\n");
	ob = push_new_object(&(sc->obj_list));
	if (!ob)
		return (-11);
	it = get_some_d(ob->coord, 3, begin + 2);
	if (!it)
		return (-41);
	if (!ft_strncmp(begin, "cy", 2))
		it = process_cylinder(it, ob);
	else if (!ft_strncmp(begin, "pl", 2))
		it = process_plane(it, ob);
	else if (!ft_strncmp(begin, "sp", 2))
		it = process_sphere(it, ob);
	if (!it)
		return (-41);
	return (1);
}
