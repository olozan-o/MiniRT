/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prepare_to_show.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olozano- <olozano-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/12 21:02:37 by oscarlo           #+#    #+#             */
/*   Updated: 2021/12/09 22:26:03 by olozano-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static void	fill_pixel(t_mlx_show *the_show, int x, int y, int *color)
{
	int	i;

	i = (x * 4)
		+ (y * the_show->size_line);
	the_show->data[i] = color[2];
	the_show->data[++i] = color[1];
	the_show->data[++i] = color[0];
	the_show->data[++i] = color[3];
	free(color);
}

int	*find_pixel(t_v3 origin, t_v3 ray, t_scene *sc)
{
	t_objs	*intersected;
	t_objs	*iter;
	double	dist;
	double	closest;

	iter = sc->obj_list;
	closest = INF;
	intersected = NULL;
	while (iter)
	{
		if (iter->type == 's')
			dist = inter_sphere(origin, ray, iter);
		else if (iter->type == 'p')
			dist = inter_plane(origin, ray, iter);
		else if (iter->type == 'c')
			dist = inter_cylinder(origin, ray, iter);
		if (dist > 0.0001 && dist < closest)
		{
			closest = dist;
			intersected = iter;
		}
		iter = iter->next;
	}
	return (get_color(origin, scale_v(ray, closest), intersected, sc));
}

int	fill_the_image(t_scene *sc, t_mlx_show *the_show)
{
	int		x_i;
	int		y_i;
	t_v3	ray_i;
	double	fov;

	x_i = -1;
	fov = sc->camera->params.x;
	while (++x_i < sc->width)
	{
		y_i = -1;
		while (++y_i < sc->height)
		{
			ray_i.x = sc->width / 2 - x_i;
			ray_i.y = y_i - sc->height / 2;
			ray_i.z = sc->width / 2 / tan(fov);
			ray_i = rotate_cam(normalize(ray_i), sc->camera->or, sc->up_v);
			fill_pixel(the_show, x_i, y_i,
				find_pixel(sc->camera->coord, ray_i, sc));
		}
	}
	return (1);
}

int	put_it_on(t_scene *sc, t_mlx_show *the_show)
{
	if (!sc)
		return (-1060);
	if (!the_show)
		return (-1061);
	if (!fill_the_image(sc, the_show))
		return (-1062);
	mlx_put_image_to_window(the_show->mlx_ptr, the_show->win_ptr,
		the_show->mlx_img, 0, 0);
	return (0);
}

int	check_all(t_scene *sc)
{
	t_objs		*it;
	t_v3		aux;

	if (color_error(sc->a_color) || color_error(sc->f_light->color))
		exit_program("Error\nWrong color formatting\n");
	if (sc->a_lum < 0 || sc->a_lum > 1)
		exit_program("Error\nAmbiance light error\n");
	initialize_v3(&aux);
	if (distance3(sc->camera->or, aux) > 1
		|| distance3(sc->camera->or, aux) < -1
		|| distance3(sc->camera->or, aux) == 0
		|| sc->camera->params.x < 0 || sc->camera->params.x > M_PI)
		exit_program("Error\nCamera error\n");
	normalize(sc->camera->or);
	if (sc->f_light->params.x < 0 || sc->f_light->params.x > 1
		|| color_error(sc->f_light->color))
		exit_program("Error\nWrong focused light parmeters\n");
	it = sc->obj_list;
	while (it)
	{
		if (object_error(it))
			exit_program("Error\nObject formatting error\n");
		it = it->next;
	}
	return (0);
}
