/* ************************************************************************** */
/*																			*/
/*														:::	  ::::::::   */
/*   math_calculs.c									 :+:	  :+:	:+:   */
/*													+:+ +:+		 +:+	 */
/*   By: olozano- <olozano-@student.42.fr>		  +#+  +:+	   +#+		*/
/*												+#+#+#+#+#+   +#+		   */
/*   Created: 2021/05/05 19:57:14 by oscarlo		   #+#	#+#			 */
/*   Updated: 2021/11/28 18:49:00 by olozano-		 ###   ########.fr	   */
/*																			*/
/* ************************************************************************** */

#include "minirt.h"

double	*normalize(double *these3)
{
	double	max;
	int		i;

	max = sqrt(dot_product(these3, these3));
	these3[0] = these3[0] / max;
	these3[1] = these3[1] / max;
	these3[2] = these3[2] / max;
/*
	i = 0;
	max = 1;
	while (i < 3)
	{
		if (fabs(these3[i]) > max)
			max = fabs(these3[i]);
		i++;
	}
	these3[0] = these3[0] / max;
	these3[1] = these3[1] / max;
	these3[2] = these3[2] / max;*/
	return (these3);
}

double	*rotate_cam(double *org, double *trans, double *up_v)
{
	double	*x_axis;
	double	*y_axis;
	double	*z_axis;
	double	*result;

	result = ft_calloc(4, sizeof(double));
	z_axis = trans;
	if (trans[1] != 1 && trans[1] != -1)
		x_axis = cross_product(up_v, z_axis);
	else
	{
		x_axis = ft_calloc(4, sizeof(double));
		x_axis[0] = trans[1];
	}
	y_axis = cross_product(z_axis, x_axis);
	result[0] = org[0] * x_axis[0] + org[1] * y_axis[0] + org[2] * z_axis[0];
	result[1] = org[0] * x_axis[1] + org[1] * y_axis[1] + org[2] * z_axis[1];
	result[2] = org[0] * x_axis[2] + org[1] * y_axis[2] + org[2] * z_axis[2];
	free(org);
	free(x_axis);
	free(y_axis);
	return (result);
}
