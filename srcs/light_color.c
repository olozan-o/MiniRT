/* ************************************************************************** */
/*																			*/
/*														:::	  ::::::::   */
/*   light_color.c									  :+:	  :+:	:+:   */
/*													+:+ +:+		 +:+	 */
/*   By: olozano- <olozano-@student.42.fr>		  +#+  +:+	   +#+		*/
/*												+#+#+#+#+#+   +#+		   */
/*   Created: 2021/11/28 13:11:58 by olozano-		  #+#	#+#			 */
/*   Updated: 2021/11/28 17:20:17 by olozano-		 ###   ########.fr	   */
/*																			*/
/* ************************************************************************** */

#include "minirt.h"

void	compute_color(int *light_color, int *obj_color)
{
	light_color[0] = (obj_color[0] * light_color[0]) / 255;
	light_color[1] = (obj_color[1] * light_color[1]) / 255;
	light_color[2] = (obj_color[2] * light_color[2]) / 255;
	if (light_color[0] > 255)
		light_color[0] = 255;
	if (light_color[1] > 255)
		light_color[1] = 255;
	if (light_color[2] > 255)
		light_color[2] = 255;
}

int	*combine_lights(double l1_c, int *l1_color, double l2_c, int *l2_color)
{
	int	*result;

	result = ft_calloc(4, sizeof(int));
	result[0] = l1_color[0] * l1_c + l2_color[0] * l2_c;
	result[1] = l1_color[1] * l1_c + l2_color[1] * l2_c;
	result[2] = l1_color[2] * l1_c + l2_color[2] * l2_c;
	return (result);
}

int	check_objects(double *point, double *light, rt_objs *iter, double *ray)
{
	double	dist;
	double	d_intersect;
	double	*to_light;

	dist = sqrt(pow(light[0] - point[0], 2) + pow(light[1] - point[1], 2)
			+ pow(light[2] - point[2], 2));
	to_light = normalize(substract(light, point));
	d_intersect = -1;
	if (iter->type == 'p')
		d_intersect = inter_plane(point, to_light, iter);
	else if (iter->type == 's')
		d_intersect = inter_sphere(point, to_light, iter);
	else if (iter->type == 'c')
		d_intersect = inter_cylinder(point, to_light, iter);
	if (d_intersect > 0.0001 && d_intersect < dist)
	{
		printf("\t\tIt Intersects with an object of type [%c] at (%f, %f, %f) at a distance of %f\n", 
			iter->type, iter->coord[0],iter->coord[1],iter->coord[2], d_intersect);
		return (0);
	}

	return (1);
}

int	*get_color(double *origin, double *ray, rt_objs *intersected, rt_scene *sc)
{
	int		*result;
	rt_objs	*iter;
	double	*point;
	double	*to_light;
	int		check;

	check = 1;
	point = add_v(origin, ray);
	to_light = normalize(substract(sc->f_light->coord, point));
	//printf("Working with origin (%f, %f, %f), then at point of intersection (%f, %f, %f). ")
	iter = sc->obj_list;
	printf("\n\nRay from camera is: (%f, %f, %f). It intersects with object of type [%c]\n", ray[0], ray[1], ray[2], intersected->type);
	printf("\tIt finds the spotlight at (%f, %f, %f) using (%f, %f, %f) \n",
		sc->f_light->coord[0], sc->f_light->coord[1], sc->f_light->coord[2], to_light[0], to_light[1], to_light[2]);
	while (iter && check)
	{
		check = check_objects(point, sc->f_light->coord, iter, ray);
		if (check)
			iter = iter->next;
	}
	free(point);
	free(to_light);
	result = combine_lights(sc->a_lum, sc->a_color, sc->f_light->params[0] * check,
			sc->f_light->color);
	printf("Combined lights are [%d, %d, %d]\n", result[0], result[1], result[2]);
	compute_color(result, intersected->color);
	printf("And when they touch the object they become [%d, %d, %d]\n", result[0], result[1], result[2]);
	return (result);
}
