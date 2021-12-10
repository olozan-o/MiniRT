/* ************************************************************************** */
/*																			*/
/*														:::	  ::::::::   */
/*   process_elements2.c								:+:	  :+:	:+:   */
/*													+:+ +:+		 +:+	 */
/*   By: olozano- <olozano-@student.42.fr>		  +#+  +:+	   +#+		*/
/*												+#+#+#+#+#+   +#+		   */
/*   Created: 2021/11/27 10:38:51 by olozano-		  #+#	#+#			 */
/*   Updated: 2021/11/28 15:11:40 by olozano-		 ###   ########.fr	   */
/*																			*/
/* ************************************************************************** */

#include "minirt.h"

int	process_ambiance(t_scene *sc, char *begin)
{
	char	*it;

	it = begin + 1;
	sc->a_lum = ft_strtod(it);
	it = advance_through(it);
	sc->a_color[0] = (int)ft_strtod(it);
	it = advance_through(it);
	sc->a_color[1] = (int)ft_strtod(it);
	it = advance_through(it);
	sc->a_color[2] = (int)ft_strtod(it);
	it = advance_through(it);
	while (*it == ' ')
		it++;
	if (!*it)
		return (11);
	else
		return (-44);
}

int	process_camera(t_scene *sc, char *begin)
{
	char	*it;
	t_objs	*this_obj;

	sc->camera = push_new_object(&(sc->camera));
	if (!sc->camera)
		return (-11);
	this_obj = sc->camera;
	this_obj->type = 'C';
	it = get_some_d(&this_obj->coord, 3, begin + 1);
	if (!it)
		return (-41);
	it = get_some_d(&this_obj->or, 3, it);
	if (!it)
		return (-41);
	it = get_some_d(&this_obj->params, 1, it);
	this_obj->params.x = this_obj->params.x * M_PI / 180 / 2;
	if (!it)
		return (-41);
	if (this_obj->or.x == 0 && this_obj->or.y == 0 && this_obj->or.z == 0)
		this_obj->or.z = 1;
	return (1);
}

int	process_light(t_scene *sc, char *begin)
{
	char	*it;
	t_objs	*this_obj;

	this_obj = push_new_object(&(sc->f_light));
	if (!this_obj)
		return (0);
	sc->f_light = this_obj;
	this_obj->type = 'L';
	it = get_some_d(&this_obj->coord, 3, begin + 1);
	if (!it)
		return (-41);
	it = get_some_d(&this_obj->params, 1, it);
	if (!it)
		return (-41);
	it = get_some_i(this_obj->color, 3, it);
	if (!it)
		return (-41);
	if (this_obj->or.x > 255 || this_obj->or.x < 0
		|| this_obj->or.y > 255 || this_obj->or.y < 0
		|| this_obj->or.z > 255 || this_obj->or.z < 0
		|| this_obj->params.x < 0 || this_obj->params.x > 1)
		return (-42);
	return (1);
}
