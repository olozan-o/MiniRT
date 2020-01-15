/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_calls.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olozano- <olozano-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/14 10:28:29 by olozano-          #+#    #+#             */
/*   Updated: 2020/01/15 19:40:47 by olozano-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"
#include <unistd.h>
#include <fcntl.h>

rt_scene	*make_a_scene(void)
{
	rt_scene	*new_scene;

	if (!(new_scene = malloc(sizeof(rt_scene))))
		return (NULL);
	new_scene->height = 0;
	new_scene->width = 0;
	new_scene->a_lum = -1;
	new_scene->a_color[0] = 0;
	new_scene->a_color[1] = 0;
	new_scene->a_color[2] = 0;
	new_scene->obj_list = NULL;
	new_scene->light_list = NULL;
	return (new_scene);
}


int main(int argc, char **argv)
{
	int			fd;
	char		*file_str;
	rt_scene	*scene_now;

	if (argc < 2)
		return (error_out(-1)); // ERROR TOO FEW ARGUMENTS == -1
	fd = open(argv[1], argc);
	if (fd < 0)
		return (error_out(1)); // ERROR OPENING == 1
	if (!(file_str = read_everything(fd)))
		return (error_out(0)); // MEMORY ALLOCATION IMPOSSIBLE == 0
	if (!(scene_now = make_a_scene()))
		return (error_out(0)); // MEMORY ALLOCATION IMPOSSIBLE == 0
	if ((fd = process_everything(file_str, scene_now)))
		return (error_out(fd)); // ERRONEOUS INFORMATION IN RT FILE == 40 - 48
	if (!show_it(scene_now))
		return (error_out(111)); // ERROR IN DISPLAYING
	return (0);
}