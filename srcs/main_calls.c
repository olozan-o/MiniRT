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

mlx_show	*rideau(rt_scene *scene)
{
	mlx_show		*the_show;

	if (!(the_show = malloc(sizeof(mlx_show))))
		return (NULL);
	the_show->mlx_ptr = mlx_init();
	the_show->mlx_img = mlx_new_image(the_show->mlx_ptr, scene->width, scene->height);
	the_show->data = mlx_get_data_addr(the_show->mlx_img,
		&the_show->bpp, &the_show->size_line, &the_show->endian);
	the_show->win_ptr = mlx_new_window(the_show->mlx_ptr, scene->width, scene->height, 
		"miniRT");
	return (the_show);
}

void	start_the_dance(mlx_show *the_show)
{
	mlx_clear_window(the_show->mlx_ptr, the_show->win_ptr);
	mlx_put_image_to_window(the_show->mlx_ptr, the_show->win_ptr,
the_show->mlx_img, 0, 0);
	//mlx_hook(the_show->win_ptr, 2, 1L << 0, handle_key, the_show);
	mlx_hook(the_show->win_ptr, 17, 1L << 17, exit_program, 0);
	mlx_loop(the_show->mlx_ptr);
}

#include <stdio.h>

int			main(int argc, char **argv)
{
	int			fd;
	char		*file_str;
	rt_scene	*scene_now;
	mlx_show	*the_show;

	if (argc < 2 || argc > 3 || (argc == 3 && (ft_strcmp(argv[2], "-save"))))
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
		return (error_out(111)); // ERROR IN INTERNAL INFO ?

	printf(" all checked, going to write\n");

	if (!(the_show = rideau(scene_now)) || (put_it_on(scene_now, the_show)))
		return (error_out(-1060));
	if (argc == 2)
		start_the_dance(the_show);
	else if (argc == 3 && !(ft_strcmp(argv[2], "-save")))
		// export_bmp(create_bmp_filename(argv[1], i), the_show);
	return (0);
}
