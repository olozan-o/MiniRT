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

double	inter_sphere(t_v3 origin, t_v3 ray, t_objs *obj)
{
	double	closer;
	double	inter_p[2];
	t_v3	aux;
	t_v3	k;

	aux = substract(origin, obj->coord);
	k.x = dot_product(ray, ray);
	k.y = 2 * dot_product(ray, aux);
	k.z = dot_product(aux, aux) - ((obj->params.x / 2) * (obj->params.x / 2));
	closer = k.y * k.y - (4 * k.x * k.z);
	if (closer < 0)
		return (-1);
	inter_p[0] = (sqrt(closer) - k.y) / (2 * k.x);
	inter_p[1] = (-sqrt(closer) - k.y) / (2 * k.x);
	if (inter_p[0] > 0.001 && inter_p[0] < inter_p[1])
		closer = inter_p[0];
	else if (inter_p[1] > 0.001)
		closer = inter_p[1];
	else
		return (-1);
	return (closer);
}

double	inter_plane(t_v3 origin, t_v3 ray, t_objs *obj)
{
	double	x;
	double	denom;
	t_v3	aux;

	denom = dot_product(obj->orient, ray);
	if (denom == 0)
		return (-1);
	aux = substract(obj->coord, origin);
	x = dot_product(obj->orient, aux) / denom;
	return (x);
}
