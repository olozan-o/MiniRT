/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect_cyl.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oscarlo <oscarlo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/29 15:19:40 by olozano-          #+#    #+#             */
/*   Updated: 2021/12/08 22:39:03 by oscarlo          ###   ########.fr       */
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

	v = scale_v(obj->orient, dot_product(ray, obj->orient));
	v = substract(ray, v);
	a = dot_product(substract(origin, obj->coord), obj->orient);
	u = scale_v(obj->orient, a);
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
	if (!((dist[0] >= 0 && dist[0] <= obj->params.y && x[0] > 0.001)
			|| (dist[1] >= 0 && dist[1] <= obj->params.y && x[0] > 0.001)))
		return (-1);
	if (dist[0] >= 0 && dist[0] <= obj->params.y && x[0] > 0.001
		&& dist[1] >= 0 && dist[1] <= obj->params.y && x[1] > 0.001)
	{
		if (x[0] < x[1])
			return (x[0]);
		else
			return (x[1]);
	}
	else if (dist[0] >= 0 && dist[0] <= obj->params.y && x[0] > 0.001)
		return (x[0]);
	else
		return (x[1]);
}

double	compute_plane(t_v3 origin, t_v3 ray, t_objs *obj, int procedure)
{
	t_v3	aux3;
	double	dd;

	if (procedure == 1)
		aux3 = add_v(obj->coord, scale_v(obj->orient, obj->params.y));
	else
		aux3 = v_dup(obj->coord);
	dd = dot_product(obj->orient, ray);
	if (!dd)
		dd = -1;
	else
		dd = dot_product(obj->orient, substract(aux3, origin)) / dd;
	return (dd);
}

double	check_caps(t_v3 origin, t_v3 ray, t_objs *obj, t_v3 ccc)
{
	double	dd;
	t_v3	aux;

	if (ccc.x == obj->coord.x && ccc.y == obj->coord.y)
		dd = compute_plane(origin, ray, obj, 0);
	else
		dd = compute_plane(origin, ray, obj, 1);
	if (dd < 0.001)
		return(-1);
	aux = add_v(origin, scale_v(ray, dd));
	if (dd > 0.001 && distance3(aux, ccc) <= obj->params.x / 2)
		return (dd);
	else
		return (-1);
}

double	best_with_caps(t_v3 origin, t_v3 ray, t_objs *obj, double inter_body)
{
	double	dd[2];
	double	caps;
	t_v3	ccc;
	t_v3	aux;

	dd[0] = check_caps(origin, ray, obj, obj->coord);
	ccc = add_v(obj->coord, (scale_v(obj->orient, obj->params.y)));
	dd[1] = check_caps(origin, ray, obj, ccc);
	caps = -1;
	aux = add_v(origin, scale_v(ray, dd[1]));
	
	if (dd[0] > 0.001 && (dd[0] < dd[1] || dd[1] < 0.001))
		caps = dd[0];
	else if (dd[1] > 0.001 && (dd[1] < dd[0] || dd[0] < 0.001))
		caps = dd[1];
	if (0 > 0.001)
	{
		printf("Caps intersect at %f, choosing between %f and %f, while body at %f\n", 
				caps, dd[0], dd[1], inter_body);
		printf("\tCylinder height being %f and radius %f\n", obj->params.y, obj->params.x / 2);
		printf(" (%f) ", distance3(aux, ccc));
		printf("\t\tLower cap coordinates:[%.2f, %.2f, %.2f], Upper cap coordinates: [%.2f, %.2f, %.2f]\n\n",
				obj->coord.x, obj->coord.y, obj->coord.z, ccc.x, ccc.y, ccc.z);
	}
	if (caps > 0.001 && (caps < inter_body || inter_body < 0.001))
		return (caps);
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
	aux = substract(scale_v(ray, x[0]), substract(obj->coord, origin));
	aux2 = substract(scale_v(ray, x[1]), substract(obj->coord, origin));
	dist[0] = dot_product(obj->orient, aux);
	dist[1] = dot_product(obj->orient, aux2);
	return (best_with_caps(origin, ray, obj, best_body(dist, x, obj)));
}
