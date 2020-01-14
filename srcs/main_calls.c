/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_calls.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olozano- <olozano-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/14 10:28:29 by olozano-          #+#    #+#             */
/*   Updated: 2020/01/14 13:14:05 by olozano-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"
#include <unistd.h>
#include <fcntl.h>


int main(int argc, char **argv)
{
	int		fd;
	char	*file_str;



	if (argc < 2)
		write(2, "ERROR :: .rt file needed\n", 25);
	fd = open(argv[1], argc);
	if (fd < 0)
		return(error_out(1));
	if (!(file_str = read_everything))
		return(error_out(0));
	if ()
}