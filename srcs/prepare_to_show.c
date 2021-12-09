/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prepare_to_show.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olozano- <olozano-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/12 21:02:37 by oscarlo           #+#    #+#             */
/*   Updated: 2021/11/29 15:28:46 by olozano-         ###   ########.fr       */
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

int	*find_pixel(t_v3 origin, t_v3 ray, t_scene *sc, t_mlx_show *the_show)
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
		if (dist > 0.001 && dist < closest)
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
			ray_i = rotate_cam(normalize(ray_i), sc->camera->orient, sc->up_v);
			fill_pixel(the_show, x_i, y_i,
				find_pixel(sc->camera->coord, ray_i, sc, the_show));
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
	t_objs		*iterator;

	return (0);
	printf("\nRESOLUTION:\n--:%d, %d\n", 
		sc->width, sc->height);

	printf("\nCAMERAS:\n");
	iterator = sc->camera;
	while (iterator)
	{
		printf("position--: %f, %f, %f\n", iterator->coord.x, iterator->coord.y,
				iterator->coord.z);
		printf("--orientation--: %f, %f, %f\n", iterator->orient.x, 
				iterator->orient.y, iterator->orient.z);
		printf("--aperture?--%f\n", iterator->params.x);
		iterator = iterator->next;
	}
	write(1, "getting to the lights\n", 23);
	printf("\nAMBIANCE LIGHT:\n--:%f, %d, %d, %d\n", 
		sc->a_lum, sc->a_color[0], sc->a_color[1], sc->a_color[2]);

	printf("\nLIGHTS:\n");
	iterator = sc->f_light;
	while (iterator)
	{
		printf("position--: %f, %f, %f\n", iterator->coord.x, iterator->coord.y,
				iterator->coord.z);
		printf("--orientation--: %f, %f, %f\n", iterator->orient.x, 
				iterator->orient.y, iterator->orient.z);
		printf("--aperture?--: %f\n", iterator->params.x);
		printf("--color--: %d, %d, %d\n", iterator->color[0], 
				iterator->color[1], iterator->color[2]);
		iterator = iterator->next;
	}

	printf("\nOBJECTS:\n");
	iterator = sc->obj_list;
	while (iterator)
	{
		printf("position--: %f, %f, %f\t", iterator->coord.x, iterator->coord.y,
				iterator->coord.z);
		printf("--other stuff--: %f, %f, %f\n", iterator->orient.x, 
				iterator->orient.y, iterator->orient.z);
		printf("--parameters--: %f, %f, %f\t", iterator->params.x, 
				iterator->params.y, iterator->params.z);
		printf("--color--: %d, %d, %d\n\n", iterator->color[0], 
				iterator->color[1], iterator->color[2]);
		iterator = iterator->next;
	}
	return (1);
}