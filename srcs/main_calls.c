/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_calls.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olozano- <olozano-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/14 10:28:29 by olozano-          #+#    #+#             */
/*   Updated: 2020/01/14 13:58:05 by olozano-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"
#include <unistd.h>
#include <fcntl.h>

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
	if (!(scene_now = malloc(sizeof(rt_scene))))
		return (error_out(0));
	if (!process_everything(file_str, scene_now))
		return (error_out(44)); // ERRONEOUS INFORMATION IN RT FILE == 44
	if (!show_it(scene_now))
		return (error_out(111)); // ERROR IN DISPLAYING
	return (0);
}