/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olozano- <olozano-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/02 16:51:39 by olozano-          #+#    #+#             */
/*   Updated: 2021/05/05 19:59:15 by olozano-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int		exit_program(void)
{
	exit(0);
	return (0);
}

int		object_error(char c)
{
/*	Sphere:-43		Plane:-44		Square:-45	*/
/*	Cylinder:-46	Triangle:-47				*/
	if (c == 's')
		return (-43);
	if (c == 'p')
		return (-44);
	if (c == 'q')
		return (-45);
	if (c == 'c')
		return (-46);
	if (c == 't')
		return (-47);
	return (-4444);
}

int		error_out(int code)
{
	if (code==11)
	{
		ft_putstr_fd("This error is an error\n", 2);
	}
	if (code==40)
	{
		ft_putstr_fd("\nAn element wasn't formatted correctly!\n", 2);
	}
	return (0);
}