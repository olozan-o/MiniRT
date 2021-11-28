/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersections.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olozano- <olozano-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/28 11:36:23 by olozano-          #+#    #+#             */
/*   Updated: 2021/11/28 13:38:38 by olozano-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

double	inter_sphere(double *origin, double *ray, rt_objs *obj)
{
	double	closer;
	double	inter_p[2];
	double	*aux;
	double	k[3];

	aux = substract(origin, obj->coord);
	k[0] = dot_product(ray, ray);
	k[1] = 2 * dot_product(ray, aux);
	k[2] = dot_product(aux, aux) - ((obj->params[0] / 2) * (obj->params[0] / 2));
	closer = k[1] * k[1] - (4 * k[0] * k[2]);
	free(aux);
	if (closer < 0)
		return (-1);
	inter_p[0] = (sqrt(closer) - k[1]) / (2 * k[0]);
	inter_p[1] = (-sqrt(closer) - k[1]) / (2 * k[0]);
	if (inter_p[0] > 0.001 && inter_p[0] < inter_p[1])
		closer = inter_p[0];
	else if (inter_p[1] > 0.001)
		closer = inter_p[0];
	else
		return (-1);
	return (closer);
}

double	inter_plane(double *origin, double *ray, rt_objs *obj)
{
	double	x;
	double	denom;
	double	*aux;

	denom = dot_product(obj->orient, ray);
	if (denom == 0)
		return(-1);
	aux = substract(obj->coord, origin);
	x = dot_product(obj->orient, aux) / denom;
	free (aux);
	return(0);
}

double	inter_cylinder(double *origin, double *ray, rt_objs *obj)
{
	return(-1);
}
