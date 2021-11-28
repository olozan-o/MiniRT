/* ************************************************************************** */
/*																			*/
/*														:::	  ::::::::   */
/*   struct_fts.c									   :+:	  :+:	:+:   */
/*													+:+ +:+		 +:+	 */
/*   By: olozano- <olozano-@student.42.fr>		  +#+  +:+	   +#+		*/
/*												+#+#+#+#+#+   +#+		   */
/*   Created: 2020/03/02 15:38:00 by olozano-		  #+#	#+#			 */
/*   Updated: 2021/11/28 15:09:34 by olozano-		 ###   ########.fr	   */
/*																			*/
/* ************************************************************************** */

#include "minirt.h"


double		*v_dup(double *this)
{
	double	*result;

	result = ft_calloc(4, sizeof(double));
	result[0] = this[0];
	result[1] = this[1];
	result[2] = this[2];
	return(result);
}

rt_objs		*push_new_object(rt_objs **begin_list)
{
	rt_objs	*new_one;

	if (!(new_one = malloc(sizeof(rt_objs))))
		return (NULL);
	new_one->coord = ft_calloc(4, sizeof(double));
	new_one->orient = ft_calloc(4, sizeof(double));
	new_one->params = ft_calloc(4, sizeof(double));
	new_one->color = ft_calloc(4, sizeof(double));
	new_one->next = *begin_list;
	*begin_list = new_one;
	return (new_one);
}

char	*get_some_i(int *things, int how_many, char *where_from)
{
	int		i;
	char	*str_backup;

	i = 0;
	str_backup = where_from;
	while (i < how_many)
	{
		things[i] = (int) ft_strtod(where_from);
		where_from = advance_through(where_from);
		i++;
	}
	if (ft_isspace(*where_from) || *where_from == '\n' || *where_from == '\0')
		return (where_from);
	return (NULL);
}

char	*get_some_d(double *things, int how_many, char *where_from)
{
	int	i;
	char	*str_backup;

	i = 0;
	str_backup = where_from;
	while (i < how_many)
	{
		things[i] = ft_strtod(where_from);
		where_from = advance_through(where_from);
		i++;
	}
	if (ft_isspace(*where_from) || *where_from == '\n' || *where_from == '\0')
	{
		return (where_from);
	}
	return (NULL);
}
