/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prepare_to_show.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olozano- <olozano-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/12 21:02:37 by oscarlo           #+#    #+#             */
/*   Updated: 2021/05/12 12:05:37 by olozano-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include <stdio.h>

int		fill_pixel(rt_scene *scene_now, t_mlx_show *the_show, double *ray, int pix)
{
	// TO BE FILLED:

	// go find what the ray intersects with
	// go find the color it gets from light hitting it
	
	// fill the 'pix' pixel with the appropriate color
	return (0);
}


int		fill_the_image(rt_scene *scene_now, t_mlx_show *the_show)
{
	int		x_i;
	int		y_i;
	double	*ray_i;
	double	fov;
	int		aux;

	compute_rotation(scene_now->camera_list->coord, scene_now->camera_list->orient);
	ray_i = ft_calloc(3, sizeof(double));
	x_i = -1;
	y_i = -1;
	fov = scene_now->camera_list->params[0];
	while (++x_i < scene_now->width)
		while (++y_i < scene_now->height)
		{
			ray_i[0] = (2 * ((x_i + 0.5) / scene_now->width) - 1) * tan(fov / 2 * M_PI / 180) 
						* scene_now->width / scene_now->height;
			ray_i[1] = (1 - 2 * (y_i + 0.5) / scene_now->height) * tan(fov / 2 * M_PI / 180);
			ray_i[2] = -1; // or 1 ??
			world_to_cam(normalize(ray_i));
			aux = y_i * the_show->size_line + the_show->bpp / 8 * x_i;
			fill_pixel(scene_now, the_show, ray_i, aux);
		}
	
	return (0);
}

int		put_it_on(rt_scene *scene_now, t_mlx_show *the_show)
{
	if (!scene_now)
		return (-1060);
	if (!the_show)
		return (-1061);
	printf ("\n* * * * * I WOULD BE PUTTING OUT AMAZING THINGS RIGHT NOW * * * * * *\n\n");
	if (!fill_the_image(scene_now, the_show))
		return (-1062);
	
	return(0);
}

int		check_all(rt_scene *sc)
{
	rt_objs		*iterator;

	printf("\nRESOLUTION:\n--:%d, %d\n", 
		sc->width, sc->height);

	printf("\nCAMERAS:\n");
	iterator = sc->camera_list;
	while (iterator)
	{
		printf("position--: %f, %f, %f\n", iterator->coord[0], iterator->coord[1],
				iterator->coord[2]);
		printf("--orientation--: %f, %f, %f\n", iterator->orient[0], 
				iterator->orient[1], iterator->orient[2]);
		write(1, "right before the aperture\n", 27);
		printf("--aperture?--%f\n", iterator->params[0]);
		write(1, "right before to the lights\n", 28);
		iterator = iterator->next;
	}
	write(1, "getting to the lights\n", 23);
	printf("\nAMBIANCE LIGHT:\n--:%f, %d, %d, %d\n", 
		sc->a_lum, sc->a_color[0], sc->a_color[1], sc->a_color[2]);

	printf("\nLIGHTS:\n");
	iterator = sc->light_list;
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