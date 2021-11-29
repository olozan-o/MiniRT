/* ************************************************************************** */
/*																			*/
/*														:::	  ::::::::   */
/*   errors.c										   :+:	  :+:	:+:   */
/*													+:+ +:+		 +:+	 */
/*   By: olozano- <olozano-@student.42.fr>		  +#+  +:+	   +#+		*/
/*												+#+#+#+#+#+   +#+		   */
/*   Created: 2020/03/02 16:51:39 by olozano-		  #+#	#+#			 */
/*   Updated: 2021/11/27 12:55:33 by olozano-		 ###   ########.fr	   */
/*																			*/
/* ************************************************************************** */

#include "minirt.h"

int	operate_key_press(int key)
{
	if (key == ESC_KEY)
		exit_program("Thank you, come again!\n");
	return (0);
}

int	exit_program(char *str)
{
	ft_putstr_fd(str, 2);
	exit(0);
	return (0);
}

int	object_error(char c)
{
	if (c == 's')
		return (-43);
	if (c == 'p')
		return (-44);
	if (c == 'c')
		return (-46);
	return (-4444);
}

int	error_out(int code)
{
	if (code == 11)
	{
		exit_program("This error is an error\n");
	}
	if (code == 40)
	{
		exit_program("Error\nAn element wasn't formatted correctly!\n");
	}
	else
		exit_program("Error\nUnknown\n");
	return (0);
}
