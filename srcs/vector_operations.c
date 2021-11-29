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

t_v3	cross_product(t_v3 one, t_v3 other)
{
	t_v3	result;

	result.x = one.y * other.z - one.z * other.y;
	result.y = one.z * other.x - one.x * other.z;
	result.z = one.x * other.y - one.y * other.x;
	return (result);
}

t_v3	scale_v(t_v3 v, double n)
{
	v.x = v.x * n;
	v.y = v.y * n;
	v.z = v.z * n;
	return (v);
}

double	dot_product(t_v3 one, t_v3 other)
{
	return (one.x * other.x + one.y * other.y + one.z * other.z);
}

t_v3	substract(t_v3 one, t_v3 other)
{
	t_v3	result;

	result.x = one.x - other.x;
	result.y = one.y - other.y;
	result.z = one.z - other.z;
	return (result);
}

t_v3	add_v(t_v3 one, t_v3 other)
{
	t_v3	result;

	result.x = one.x + other.x;
	result.y = one.y + other.y;
	result.z = one.z + other.z;
	return (result);
}
