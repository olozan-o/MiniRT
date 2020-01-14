/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olozano- <olozano-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/14 12:31:02 by olozano-          #+#    #+#             */
/*   Updated: 2020/01/14 13:26:44 by olozano-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>


typedef	struct	objs
{
		char	type;
		int		coord[3];
		int		orient[3];
		int		params[3];
		int		color[3];
		struct objs	*next;
}				rt_objs;

typedef	struct	lights
{
		int			coord[3];
		int				color[3];
		int				lum;
		struct lights	*next;
}				rt_lights;

typedef	struct 	scene
{
		int			height;
		int			width;
		int			a_lum;
		int			a_color[3];
		rt_objs		**obj_list;
		rt_lights	**light_list;
}				rt_scene;

char		*read_everything(int fd);
size_t		ft_strlcat(char *dst, const char *src, size_t dstsize);
