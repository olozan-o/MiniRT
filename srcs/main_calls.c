/* ************************************************************************** */
/*																			*/
/*														:::	  ::::::::   */
/*   main_calls.c									   :+:	  :+:	:+:   */
/*													+:+ +:+		 +:+	 */
/*   By: olozano- <olozano-@student.42.fr>		  +#+  +:+	   +#+		*/
/*												+#+#+#+#+#+   +#+		   */
/*   Created: 2020/01/14 10:28:29 by olozano-		  #+#	#+#			 */
/*   Updated: 2021/11/28 16:57:28 by olozano-		 ###   ########.fr	   */
/*																			*/
/* ************************************************************************** */

#include "minirt.h"
#include <unistd.h>
#include <fcntl.h>

t_scene	*make_a_scene(void)
{
	t_scene	*new_sc;

	new_sc = malloc(sizeof(t_scene));
	if (!new_sc)
		return (NULL);
	new_sc->height = HEIGHT;
	new_sc->width = WIDTH;
	new_sc->a_lum = -1;
	new_sc->a_color = ft_calloc(3, sizeof(int));
	new_sc->obj_list = NULL;
	new_sc->f_light = NULL;
	new_sc->camera = NULL;
	new_sc->up_v.x = 0;
	new_sc->up_v.y = -1;
	new_sc->up_v.z = 0;
	return (new_sc);
}

t_mlx_show	*rideau(t_scene *sc)
{
	t_mlx_show		*the_show;

	the_show = malloc(sizeof(t_mlx_show));
	if (!the_show)
		exit_program("Error\nAllocation Impossible\n");
	the_show->mlx_ptr = mlx_init();
	the_show->mlx_img = mlx_new_image(the_show->mlx_ptr, sc->width, sc->height);
	the_show->data = mlx_get_data_addr(the_show->mlx_img,
			&the_show->bpp, &the_show->size_line, &the_show->endian);
	the_show->win_ptr = mlx_new_window(the_show->mlx_ptr, sc->width,
			sc->height, "miniRT");
	mlx_hook(the_show->win_ptr, 2, (1L << 0), operate_key_press, NULL);
	mlx_hook(the_show->win_ptr, 17, (1L << 17), exit_program, THANKS);
	the_show->bpp = 600;
	return (the_show);
}

void	start_the_dance(t_mlx_show *the_show)
{
	mlx_clear_window(the_show->mlx_ptr, the_show->win_ptr);
	mlx_put_image_to_window(the_show->mlx_ptr, the_show->win_ptr,
		the_show->mlx_img, 0, 0);
	mlx_loop(the_show->mlx_ptr);
}

int	main(int argc, char **argv)
{
	int			fd;
	char		*file_str;
	t_scene		*sc_now;
	t_mlx_show	*the_show;

	if (argc < 2 || argc > 3 || (argc == 3 && (ft_strcmp(argv[2], "-save"))))
		return (error_out(-1));
	fd = open(argv[1], O_RDONLY);
	if (fd < 0)
		return (error_out(1));
	printf("\n\nBeginning... ");
	file_str = read_everything(fd);
	sc_now = make_a_scene();
	printf("everything read.\nProcessing now...");
	process_everything(file_str, sc_now);
	free(file_str);
	printf(" all processed, going to check\n");
	check_all(sc_now);
	printf(" all checked, going to write\n");
	the_show = rideau(sc_now);
	put_it_on(sc_now, the_show);
	printf("\nCurtain's up! \n\n");
	if (argc == 2)
		start_the_dance(the_show);
	exit(0);
}
