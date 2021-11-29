/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect_cyl.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olozano- <olozano-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/29 15:19:40 by olozano-          #+#    #+#             */
/*   Updated: 2021/11/29 15:20:27 by olozano-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	cy_calculs(t_v3 origin, t_v3 ray, t_objs *obj, double x[2])
{
	t_v3	v;
	t_v3	u;
	double	a;
	double	b;
	double	c;

	v = scale_v(v_dup(obj->orient), dot_product(ray, obj->orient));
	v = substract(ray, v);
	a = dot_product(substract(origin, obj->coord), obj->orient);
	u = scale_v(v_dup(obj->orient), a);
	u = substract(substract(origin, obj->coord), u);
	a = dot_product(v, v);
	b = 2 * dot_product(v, u);
	c = dot_product(u, u) - pow(obj->params.x / 2, 2);
	x[0] = (sqrt(pow(b, 2) - 4 * a * c) - b) / (2 * a);
	x[1] = (-sqrt(pow(b, 2) - 4 * a * c) - b) / (2 * a);
	return (1);
}

double	best_body(double dist[2], double x[2], t_objs *obj)
{
	if (!((dist[0] >= 0 && dist[0] <= obj->params.y && x[0] > 0.0001)
			|| (dist[1] >= 0 && dist[1] <= obj->params.y && x[0] > 0.0001)))
		return (-1);
	if (dist[0] >= 0 && dist[0] <= obj->params.y && x[0] > 0.0001
		&& dist[1] >= 0 && dist[1] <= obj->params.y && x[1] > 0.0001)
	{
		if (x[0] < x[1])
			return (x[0]);
		else
			return (x[1]);
	}
	else if (dist[0] >= 0 && dist[0] <= obj->params.y && x[0] > 0.0001)
		return (x[0]);
	else
		return (x[1]);
}

double	compute_plane(t_v3 origin, t_v3 ray, t_objs *obj, double dd[2])
{
	t_v3	aux3;

	aux3 = add_v(obj->coord, scale_v(v_dup(obj->orient), obj->params.y));
	dd[1] = dot_product(obj->orient, ray);
	if (!dd[1])
		dd[1] = -1;
	else
		dd[1] = dot_product(obj->orient, substract(aux3, origin)) / dd[1];
	if (dd[0] < 0 && dd[1] < 0)
		return (-1);
	if (dd[0] < 0)
		dd[0] = dd[1];
	if (dd[1] < 0)
		dd[1] = dd[0];
	if (dd[1] < dd[0])
		dd[0] = dd[1];
	return (dd[0]);
}

double	best_with_caps(t_v3 origin, t_v3 ray, t_objs *obj, double inter_body)
{
	double	dd[2];
	t_v3	aux1;
	t_v3	aux2;

	dd[0] = inter_plane(origin, ray, obj);
	dd[1] = compute_plane(origin, ray, obj, dd);
	aux1 = add_v(origin, scale_v(v_dup(ray), dd[0]));
	aux2 = add_v(origin, scale_v(v_dup(ray), dd[1]));
	if (dd[0] > 0.0001 && distance3(aux1, obj->coord) <= obj->params.y
		&& dd[1] > 0.0001 && distance3(aux2, obj->coord) <= obj->params.y)
		if (dd[1] < dd[0])
			dd[0] = dd[1];
	else if (dd[1] > 0.0001 && distance3(aux2, obj->coord) <= obj->params.y)
		dd[0] = dd[1];
	else if (dd[0] > 0.0001 && distance3(aux1, obj->coord) > obj->params.y
		&& dd[1] > 0.0001 && distance3(aux2, obj->coord) > obj->params.y)
		return (-1);
	if (dd[0] > 0.0001 && dd[0] < inter_body)
		return (dd[0]);
	if (dd[1] > 0.0001 && dd[1] < inter_body)
		return (dd[1]);
	return (inter_body);
}

double	inter_cylinder(t_v3 origin, t_v3 ray, t_objs *obj)
{
	double	dist[2];
	t_v3	aux;
	t_v3	aux2;
	double	x[2];
	t_v3	final_dist;

	cy_calculs(origin, ray, obj, x);
	aux2 = scale_v(v_dup(ray), x[0]);
	aux = substract(aux2, substract(obj->coord, origin));
	dist[0] = dot_product(obj->orient, aux);
	aux2 = scale_v(v_dup(ray), x[1]);
	aux = substract(aux2, substract(obj->coord, origin));
	dist[1] = dot_product(obj->orient, aux);
	return (best_with_caps(origin, ray, obj, best_body(dist, x, obj)));
}
