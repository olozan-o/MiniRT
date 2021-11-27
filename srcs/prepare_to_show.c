/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prepare_to_show.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olozano- <olozano-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/12 21:02:37 by oscarlo           #+#    #+#             */
/*   Updated: 2021/11/27 23:03:31 by olozano-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static void	fill_pixel(t_mlx_show *the_show, int x, int y, t_color color)
{
	int	i;

	i = (x * the_show->bpp / 8)
		+ (y * the_show->size_line);
	the_show->data[i] = color.channel[3];
	the_show->data[++i] = color.channel[2];
	the_show->data[++i] = color.channel[1];
	the_show->data[++i] = color.channel[0];
}

int		find_pixel(double *origin, double *ray, rt_scene *sc)
{
	// TO BE FILLED:

	// go find what the ray intersects with
	// go find the color it gets from light hitting it
	
	// fill the 'pix' pixel with the appropriate color
	return (0);
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
			//ray_i = cam_here(sc, x_i, y_i);
			ray_i[0] = x_i - sc->width / 2;
			ray_i[1] = y_i - sc->height / 2;
			ray_i[2] = sc->width / 2 / tan(fov);
			normalize(ray_i);
			//if (y_i % 50 == 0)
			//	printf("\nx=%d, y=%d, then: %f or %f or %f \t", x_i, y_i, ray_i[0], ray_i[1], ray_i[2]);
			ray_i = rotate_cam(ray_i, sc->camera->orient, sc->up_v);
			//if (y_i % 50 == 0)
			//	printf("\n\tnormalized:: %f or %f or %f \t", ray_i[0], ray_i[1], ray_i[2]);
			//world_to_cam(ray_i, sc->rot_m);
			//if (y_i % 50 == 0)
			//	printf("\t\t RAY! {%f,%f,%f}", ray_i[0], ray_i[1], ray_i[2]);
			find_pixel(sc->camera->coord, ray_i, sc);
		}
		printf("\n\n");
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