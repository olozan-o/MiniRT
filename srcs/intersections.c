/* ************************************************************************** */
/*																			*/
/*														:::	  ::::::::   */
/*   intersections.c									:+:	  :+:	:+:   */
/*													+:+ +:+		 +:+	 */
/*   By: olozano- <olozano-@student.42.fr>		  +#+  +:+	   +#+		*/
/*												+#+#+#+#+#+   +#+		   */
/*   Created: 2021/11/28 11:36:23 by olozano-		  #+#	#+#			 */
/*   Updated: 2021/11/28 17:26:07 by olozano-		 ###   ########.fr	   */
/*																			*/
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

	if (inter_p[0] > 0.0001 && inter_p[1] < inter_p[2])
		closer = inter_p[0];
	else if (inter_p[1] > 0.0001)
		closer = inter_p[1];
	else
		return (-1);
	//printf("\t\t::::CIRCLE::: From solutions %f and %f, we chose %f\n", inter_p[0], inter_p[1], closer);
	return (closer);
}

double	inter_plane(double *origin, double *ray, rt_objs *obj)
{
	double	x;
	double	denom;
	double	*aux;

	//printf("\t\t\t---checking for plane, ");
	denom = dot_product(obj->orient, ray);
	//printf("and got a denom of %f\n", denom);
	if (denom == 0)
		return(-1);
	aux = substract(obj->coord, origin);
	x = dot_product(obj->orient, aux) / denom;
	free (aux);
	return(x);
}


int		cy_calculs(double *origin, double *ray, rt_objs *obj, double x[2])
{
	double	*v;
	double	*u;
	double	a;
	double	b;
	double	c;

	v = v_dup(obj->orient);
	scale_v(v, dot_product(ray, obj->orient));
	v = substract(ray, v);
	a = dot_product(substract(origin, obj->coord), obj->orient);
	u = v_dup(obj->orient);
	scale_v(u, a); 
	u = substract(substract(origin, obj->coord), u);
	a = dot_product(v, v);
	b = 2 * dot_product(v, u);
	c = dot_product(u, u) - pow(obj->params[0] / 2, 2);
	x[0] = (sqrt(pow(b, 2) - 4 * a * c) - b) / (2 * a);
	x[1] = (sqrt(- pow(b, 2) - 4 * a * c) - b) / (2 * a);
	return(1);
}

double	inter_cylinder(double *origin, double *ray, rt_objs *obj)
{
	double	dist[2];
	double	*aux;
	double	*aux2;
	double	x[2];

	cy_calculs(origin, ray, obj, x);
	aux2 = v_dup(ray);
	scale_v(aux2, x[0]);
	aux = substract(aux2, substract(obj->coord, origin));
	dist[0] = dot_product(obj->orient, aux);
	free(aux2);
	aux2 = v_dup(ray);
	scale_v(aux2, x[1]);
	aux = substract(aux2, substract(obj->coord, origin));
	dist[1] = dot_product(obj->orient, aux);
	if (!((dist[0] >= 0 && dist[0] <= obj->params[1] && x[0] > 0.0001)
		|| (dist[1] >= 0 && dist[1] <= obj->params[1] && x[0] > 0.0001)))
		return(-1);
	return(x[0]);
}
