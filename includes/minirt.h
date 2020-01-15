/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olozano- <olozano-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/14 12:31:02 by olozano-          #+#    #+#             */
/*   Updated: 2020/01/15 19:43:48 by olozano-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H

# define	MINIRT_H

# define	BUFFER_SIZE 128
# include <stdlib.h>

typedef	struct	objs
{
		char	type;
		double	coord[3];
		double	orient[3];
		double	params[3];
		int		color[3];
		struct objs	*next;
}				rt_objs;

typedef	struct	lights
{
		double			coord[3];
		double			lum;
		int				color[3];
		struct lights	*next;
}				rt_lights;

typedef	struct 	scene
{
		int			height;
		int			width;
		double		a_lum;
		int			a_color[3];
		rt_objs		*obj_list; // to be rechecked :: single or double pointers ??
		rt_lights	*light_list;
}				rt_scene;

char		*read_everything(int fd);
int			*process_everything(char *all, rt_scene	*this_scene);

size_t		ft_strlcat(char *dst, const char *src, size_t dstsize);
char		*ft_strchr(const char *s, int c);
int			ft_atoi(const char *nptr);
int			advance_through(char *this, int i);

#endif