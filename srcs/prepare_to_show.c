/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prepare_to_show.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olozano- <olozano-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/12 21:02:37 by oscarlo           #+#    #+#             */
/*   Updated: 2021/11/28 13:31:59 by olozano-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static void	fill_pixel(t_mlx_show *the_show, int x, int y, t_color *color)
{
	int	i;

	i = (x * 4)
		+ (y * the_show->size_line);
	if (x == 500)
		printf("Colors at (%d, %d): [%hhu, %hhu, %hhu, %hhu], \t bpp = %d\n", x, y,
				color->channel[0], color->channel[1], color->channel[2], color->channel[3], the_show->bpp);

	the_show->data[i] = color->channel[3];
	the_show->data[++i] = color->channel[2];
	the_show->data[++i] = color->channel[1];
	the_show->data[++i] = color->channel[0];
	free(color);
}

t_color	*find_pixel(double *origin, double *ray, rt_scene *sc, t_mlx_show *the_show)
{
	rt_objs	*intersected;
	rt_objs	*iter;
	double	dist;
	double	closest;
	t_color	color;

	// TO BE FILLED:

	// go find what the ray intersects with
	// go find the color it gets from light hitting it
	
	// fill the 'pix' pixel with the appropriate color
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
	scale_v(ray, closest);
	return (get_color(origin, ray, intersected, sc));
}


int		fill_the_image(rt_scene *sc, t_mlx_show *the_show)
{
	int		x_i;
	int		y_i;
	double	*ray_i;
	double	fov;

	ray_i = ft_calloc(3, sizeof(double));
	x_i = -1;
	fov = sc->camera->params[0];
	while (++x_i < sc->width)
	{
		y_i = -1;
		while (++y_i < sc->height)
		{
			ray_i[0] = x_i - sc->width / 2;
			ray_i[1] = y_i - sc->height / 2;
			ray_i[2] = sc->width / 2 / tan(fov);
			normalize(ray_i);
			ray_i = rotate_cam(ray_i, sc->camera->orient, sc->up_v);
			fill_pixel(the_show, x_i, y_i, 
				find_pixel(sc->camera->coord, ray_i, sc, the_show));
		}
	}
	free(ray_i);
	return (1);
}

int		put_it_on(rt_scene *sc, t_mlx_show *the_show)
{
	if (!sc)
		return (-1060);
	if (!the_show)
		return (-1061);
	printf ("\n* * * * * I WOULD BE PUTTING OUT AMAZING THINGS RIGHT NOW * * * * * *\n\n");
	if (!fill_the_image(sc, the_show))
		return (-1062);
	mlx_put_image_to_window(the_show->mlx_ptr, the_show->win_ptr, the_show->mlx_img, 0, 0);
	return(0);
}

int		check_all(rt_scene *sc)
{
	rt_objs		*iterator;

	printf("\nRESOLUTION:\n--:%d, %d\n", 
		sc->width, sc->height);

	printf("\nCAMERAS:\n");
	iterator = sc->camera;
	while (iterator)
	{
		printf("position--: %f, %f, %f\n", iterator->coord[0], iterator->coord[1],
				iterator->coord[2]);
		printf("--orientation--: %f, %f, %f\n", iterator->orient[0], 
				iterator->orient[1], iterator->orient[2]);
		printf("--aperture?--%f\n", iterator->params[0]);
		iterator = iterator->next;
	}
	write(1, "getting to the lights\n", 23);
	printf("\nAMBIANCE LIGHT:\n--:%f, %d, %d, %d\n", 
		sc->a_lum, sc->a_color[0], sc->a_color[1], sc->a_color[2]);

	printf("\nLIGHTS:\n");
	iterator = sc->f_light;
	while (iterator)
	{
		printf("position--: %f, %f, %f\n", iterator->coord[0], iterator->coord[1],
				iterator->coord[2]);
		printf("--orientation--: %f, %f, %f\n", iterator->orient[0], 
				iterator->orient[1], iterator->orient[2]);
		printf("--aperture?--: %f\n", iterator->params[0]);
		printf("--color--: %f, %f, %f\n", iterator->color[0], 
				iterator->color[1], iterator->color[2]);
		iterator = iterator->next;
	}

	printf("\nOBJECTS:\n");
	iterator = sc->obj_list;
	while (iterator)
	{
		printf("position--: %f, %f, %f\t", iterator->coord[0], iterator->coord[1],
				iterator->coord[2]);
		printf("--other stuff--: %f, %f, %f\n", iterator->orient[0], 
				iterator->orient[1], iterator->orient[2]);
		printf("--parameters--: %f, %f, %f\t", iterator->params[0], 
				iterator->params[1], iterator->params[2]);
		printf("--color--: %f, %f, %f\n\n", iterator->color[0], 
				iterator->color[1], iterator->color[2]);
		iterator = iterator->next;
	}
	return (1);
}