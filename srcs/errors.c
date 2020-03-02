/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olozano- <olozano-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/02 16:51:39 by olozano-          #+#    #+#             */
/*   Updated: 2020/03/02 17:02:34 by olozano-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

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
}
