/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prepare_to_show.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oscarlo <oscarlo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/12 21:02:37 by oscarlo           #+#    #+#             */
/*   Updated: 2021/04/13 11:50:02 by oscarlo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include <stdio.h>

int		put_it_on(rt_scene *scene_now, mlx_show *the_show)
{
	if (!scene_now)
		return (-1060);
	if (!the_show)
		return (-1061);
	printf ("\n* * * * * I WOULD BE PUTTING OUT AMAZING THINGS RIGHT NOW * * * * * *\n\n");
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
		printf("--aperture?--%f\n", iterator->params[0]);
		iterator = iterator->next;
	}
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