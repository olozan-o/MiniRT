/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_elements1.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olozano- <olozano-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/15 19:29:11 by olozano-          #+#    #+#             */
/*   Updated: 2020/03/02 17:02:33 by olozano-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int		process_ambiance(rt_scene *sc, char *begin)
{
	int i;

	i = 1;
	sc->a_lum = (int)ft_strtod(begin + i);
	i = advance_through(begin + i);
	sc->a_color[0] = (int)ft_strtod(begin + i);
	i = advance_through(begin + i);
	sc->a_color[1] = (int)ft_strtod(begin + i);
	i = advance_through(begin + i);
	sc->a_color[2] = (int)ft_strtod(begin + i);
	i = advance_through(begin + i);
	if (!begin[i])
		return (11); // correct, the element has an ending
	else
		return (-44);
}

int		process_camera(rt_scene *sc, char *begin)
{
	int		i;
	rt_objs	*this_obj;

	if (!(this_obj = push_new_object(&(sc->camera_list))))
		return (0);
	this_obj->type = 'C';
	i = 1;
	if (!(i = i + get_some_d(this_obj->coord, 3, begin + i)))
		return (-41); // ERORR wrong CAMERA information formating
	if (!(i = i + get_some_d(this_obj->orient, 3, begin + i)))
		return (-41);
	if (!(i = i + get_some_d(this_obj->params, 1, begin + i)))
		return (-41);
	if (this_obj->orient[0] > 1 || this_obj->orient[0] < -1
		|| this_obj->orient[1] > 1 || this_obj->orient[1] < -1
		|| this_obj->orient[2] > 1 || this_obj->orient[2] < -1
		|| this_obj->params[0] < 0 || this_obj->params[0] > 180)
		return (-41);
	return (1);
}

int		process_light(rt_scene *sc, char *begin)
{
	int		i;
	rt_objs	*this_obj;

	if (!(this_obj = push_new_object(&(sc->light_list))))
		return (0);
	this_obj->type = 'L';
	i = 1;
	if (!(i = i + get_some_d(this_obj->coord, 3, begin + i)))
		return (-42); // ERORR wrong LIGHT information formating
	if (!(i = i + get_some_d(this_obj->params, 1, begin + i)))
		return (-42);
	if (!(i = i + get_some_d(this_obj->color, 3, begin + i)))
		return (-42);
	if (this_obj->orient[0] > 255 || this_obj->orient[0] < 0
		|| this_obj->orient[1] > 255 || this_obj->orient[1] < 0
		|| this_obj->orient[2] > 255 || this_obj->orient[2] < 0
		|| this_obj->params[0] < 0 || this_obj->params[0] > 1)
		return (-42);
	return (1);
}

int		process_object(rt_scene *sc, char *begin)
{
	int		i;
	rt_objs	*ob;

	if (!(ob = push_new_object(&(sc->light_list))))
		return (0);
	i = 1;
	if (begin[0] == 's' && begin[1] == 'q')
		ob->type = 'q';
	else
		ob->type = begin[0];
	if (!(i = i + get_some_d(ob->coord, 3, begin + i)))
		return (object_error(ob->type));
	if (ob == 'p' || ob == 'q' || ob == 'c' || ob == 't')
		if (!(i = i + get_some_d(ob->orient, 3, begin + i)))
			return (object_error(ob->type));
	if (ob == 's' || ob == 'q' || ob == 'c')
		if (!(i = i + get_some_d(ob->params, 1, begin + i)))
			return (object_error(ob->type));
	i = i + get_some_d(ob->params + 1, 1, begin + i);
	if (ob == 't')
		if (!(i = i + get_some_d(ob->params, 3, begin + i)))
			return (object_error(ob->type));
	/* COLOR */
	if (!(i = i + get_some_d(ob->color, 3, begin + i)))
			return (object_error(ob->type));
	return(1);
}
