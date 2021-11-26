/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_elements1.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olozano- <olozano-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/15 19:29:11 by olozano-          #+#    #+#             */
/*   Updated: 2021/11/27 00:06:11 by olozano-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int		process_ambiance(rt_scene *sc, char *begin)
{
	char *it;

	it = begin + 1;
	sc->a_lum = ft_strtod(it);
	it = advance_through(it);
	sc->a_color[0] = (int)ft_strtod(it);
	it = advance_through(it);
	sc->a_color[1] = (int)ft_strtod(it);
	it = advance_through(it);
	sc->a_color[2] = (int)ft_strtod(it);
	it = advance_through(it);
	while (*it == ' ')
		it++;
	if (!*it)
		return (11); // correct, the element has an ending
	else
		return (-44);
}

int		process_camera(rt_scene *sc, char *begin)
{
	char	*it;
	rt_objs	*this_obj;

	if (sc->camera)
		exit_program("ERROR: Multiple cameras in sight\n");
	if (!(sc->camera = push_new_object(&(sc->camera))))
		return (-11);
	this_obj = sc->camera;
	this_obj->type = 'C';
	it = get_some_d(this_obj->coord, 3, begin + 1);
	if (!it)
		return (-41); // ERORR wrong CAMERA information formating
	it = get_some_d(this_obj->orient, 3, it);
	if (!it)
		return (-41);
	it = get_some_d(this_obj->params, 1, it);
	if (!it)
		return (-41);
	printf("FINISHED ELEMENT\n\n");

	if (this_obj->orient[0] > 1 || this_obj->orient[0] < -1
		|| this_obj->orient[1] > 1 || this_obj->orient[1] < -1
		|| this_obj->orient[2] > 1 || this_obj->orient[2] < -1
		|| this_obj->params[0] < 0 || this_obj->params[0] > 180)
		return (-41);
	return (1);
}

int		process_light(rt_scene *sc, char *begin)
{
	char	*it;
	rt_objs	*this_obj;
	int		aux;

	if (!(this_obj = push_new_object(&(sc->f_light))))
		return (0);
	this_obj->type = 'L';
	it = get_some_d(this_obj->coord, 3, begin + 1);
	if (!it)
		return (-41); // ERORR wrong LIGHT information formating
	it = get_some_d(this_obj->params, 1, it);
	if (!it)
		return (-41);
	it = get_some_d(this_obj->color, 3, it);
	if (!it)
		return (-41);
	if (this_obj->orient[0] > 255 || this_obj->orient[0] < 0
		|| this_obj->orient[1] > 255 || this_obj->orient[1] < 0
		|| this_obj->orient[2] > 255 || this_obj->orient[2] < 0
		|| this_obj->params[0] < 0 || this_obj->params[0] > 1)
		return (-42);
	return (1);
}

int		process_object(rt_scene *sc, char *begin)
{
	char	*it;
	rt_objs	*ob;
	int		aux;

	if ((ft_strncmp(begin, "sp", 2) && ft_strncmp(begin, "pl", 2)
		&& ft_strncmp(begin, "cy", 2)) || !ft_isspace(begin[2]))
	{
		printf("ERROR: unknown element: %d %d %d %d\n", ft_strncmp(begin, "sp", 2), ft_strncmp(begin, "pl", 2), ft_strncmp(begin, "cy", 2), ft_isspace(begin[1]));
		return(-4);
	}
	if (!(ob = push_new_object(&(sc->obj_list))))
		return (-11);
	it = get_some_d(ob->coord, 3, begin + 2);
	if (!it)
		return(-41);
	if (!ft_strncmp(begin, "pl", 2) || !ft_strncmp(begin, "cy", 2))
	{
		it = get_some_d(ob->orient, 3, it);
		if (!it)
			return(-41);
	}
	if (!ft_strncmp(begin, "cy", 2))
	{
		it = get_some_d(ob->params, 2, it);
		if (!it)
			return(-41);
	}
	return(1);
}
