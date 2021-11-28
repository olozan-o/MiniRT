/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light_color.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olozano- <olozano-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/28 13:11:58 by olozano-          #+#    #+#             */
/*   Updated: 2021/11/28 14:09:50 by olozano-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	compute_color(t_color color_now, double *

double	*combine_lights(double l1_coeff, double *l1_color, double l2_coeff, double *l2_color)
{
	double	*result;

	result = ft_calloc(4, sizeof(double));
	result[0] = l1_color[0] * l1_coeff + l2_color[0] * l2_coeff;
	result[1] = l1_color[1] * l1_coeff + l2_color[1] * l2_coeff;
	result[2] = l1_color[2] * l1_coeff + l2_color[2] * l2_coeff;
	return (result);
}

t_color	*get_color(double *origin, double *ray, rt_objs *intersected, rt_scene *sc)
{
	t_color	*result;
	rt_objs	*iter;
	double	*point;
	double	*to_light;
	int		check;

	check = 1;
	point = add(origin, ray);
	to_light = normalize(substract(sc->f_light->coord, point));
	iter = sc->obj_list;
	while (iter)
	{
		if (iter->type == 'p' && inter_plane(point, to_light, iter) > 0)
			check = 0;
		else if (iter->type == 's' && inter_plane(point, to_light, iter) > 0)
			check = 0;
		else if (iter->type == 'c' && inter_plane(point, to_light, iter) > 0)
			check = 0;
		iter = iter->next;
	}
	free(point);
	free(to_light);
	result = combine_lights(sc->a_lum, sc->a_color, sc->f_light->params[0] * check, sc->f_light->color));
	compute_color(result, intersected->color);
	return (result);
}