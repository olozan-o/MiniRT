/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_calls.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oscarlo <oscarlo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/14 10:28:29 by olozano-          #+#    #+#             */
/*   Updated: 2021/04/13 11:37:27 by oscarlo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
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
	new_scene->a_color = ft_calloc(3, sizeof(int));
	new_scene->obj_list = NULL;
	return (new_scene);
}

#include <stdio.h>

int			main(int argc, char **argv)
{
	int			fd;
	char		*file_str;
	rt_scene	*scene_now;

	if (argc < 2)
		return (error_out(-1)); // ERROR TOO FEW ARGUMENTS == -1
	fd = open(argv[1], O_RDONLY);
	if (fd < 0)
		return (error_out(1)); // ERROR OPENING == 1
	
	printf("\n\nBeginning... ");

	if (!(file_str = read_everything(fd)))
		return (error_out(0)); // MEMORY ALLOCATION IMPOSSIBLE == 0

	printf("everything read.\n");

	if (!(scene_now = make_a_scene()))
		return (error_out(0)); // MEMORY ALLOCATION IMPOSSIBLE == 0

	printf("Processing now...");
	
	if ((fd = process_everything(file_str, scene_now)))
		return (error_out(fd)); // ERRONEOUS INFORMATION IN RT FILE == 40 - 48

	printf(" all processed, going to check\n");

	if (!check_all(scene_now))
		return (error_out(111)); // ERROR IN DISPLAYING
	return (0);
}
