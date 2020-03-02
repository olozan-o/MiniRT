/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olozano- <olozano-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/14 12:31:02 by olozano-          #+#    #+#             */
/*   Updated: 2020/03/02 16:56:26 by olozano-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H

# define	MINIRT_H

# define	BUFFER_SIZE 128
# include <stdlib.h>

typedef	struct	objs
{
		char	type;
		double	*coord;
		double	*orient;
		double	*params;
		double	*color;
		struct objs	*next;
}				rt_objs;

typedef	struct 	scene
{
		int			height;
		int			width;
		double		a_lum;
		int			*a_color;
		rt_objs		*obj_list; // to be rechecked :: single or double pointers ??
		rt_objs		*camera_list; // to be rechecked :: single or double pointers ??
		rt_objs		*light_list;
}				rt_scene;

/*			CARCASSE FUNCTIONS		*/
char		*read_everything(int fd);
int			*process_everything(char *all, rt_scene	*this_scene);

/*		INTERNAL STRUCT FUNCTIONS	*/
int			get_some_d(double	*things, int how_many, char	*where_from);
rt_objs		*push_new_object(rt_objs **begin_list);
int			object_error(char c);

/*			STR FUNCTIONS			*/
char		**ft_split(char const *s, char c);
size_t		ft_strlcat(char *dst, const char *src, size_t dstsize);
char		*ft_strchr(const char *s, int c);
int			advance_through(char *this);
double		ft_strtod(const char *str);
void		*ft_calloc(size_t nmemb, size_t size);

#endif