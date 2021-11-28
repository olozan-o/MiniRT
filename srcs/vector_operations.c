/* ************************************************************************** */
/*																			*/
/*														:::	  ::::::::   */
/*   vector_operations.c								:+:	  :+:	:+:   */
/*													+:+ +:+		 +:+	 */
/*   By: olozano- <olozano-@student.42.fr>		  +#+  +:+	   +#+		*/
/*												+#+#+#+#+#+   +#+		   */
/*   Created: 2021/11/28 18:49:51 by olozano-		  #+#	#+#			 */
/*   Updated: 2021/11/28 18:49:55 by olozano-		 ###   ########.fr	   */
/*																			*/
/* ************************************************************************** */

#include "minirt.h"

double	*cross_product(double *one, double *other)
{
	double	*result;

	result = ft_calloc(3, sizeof(double));
	result[0] = one[1] * other[2] - one[2] * other[1];
	result[1] = one[2] * other[0] - one[0] * other[2];
	result[2] = one[0] * other[1] - one[1] * other[0];
	return (result);
}

void	scale_v(double *v, double n)
{
	v[0] = v[0] * n;
	v[1] = v[1] * n;
	v[2] = v[2] * n;
}

double	dot_product(double *one, double *other)
{
	return (one[0] * other[0] + one[1] * other[1] + one[2] * other[2]);
}

double	*substract(double *one, double *other)
{
	double	*result;

	result = ft_calloc(3, sizeof(double));
	result[0] = one[0] - other[0];
	result[1] = one[1] - other[1];
	result[2] = one[2] - other[2];
	return (result);
}

double	*add_v(double *one, double *other)
{
	double	*result;

	result = ft_calloc(3, sizeof(double));
	result[0] = one[0] + other[0];
	result[1] = one[1] + other[1];
	result[2] = one[2] + other[2];
	return (result);
}
