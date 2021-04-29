/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oscarlo <oscarlo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/14 12:31:02 by olozano-          #+#    #+#             */
/*   Updated: 2021/04/12 23:18:43 by oscarlo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H

# define	MINIRT_H

# define	BUFFER_SIZE 128
# include <stdlib.h>
# include <unistd.h>
# include <mlx.h>

typedef struct	show
{
		void	*mlx_ptr;
		void	*win_ptr;
		void	*mlx_img;
		char	*data;
		int		bpp;
		int		size_line;
		int		endian;

}				mlx_show;

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

/*			PARSING FUNCTIONS			*/
char		*read_everything(int fd);
int			process_everything(char *all, rt_scene	*this_scene);
int			process_ambiance(rt_scene *sc, char *begin);
int			process_camera(rt_scene *sc, char *begin);
int			process_light(rt_scene *sc, char *begin);
int			process_object(rt_scene *sc, char *begin);

/*			INTERNAL STRUCT FUNCTIONS	*/
int			get_some_d(double	*things, int how_many, char	*where_from);
rt_objs		*push_new_object(rt_objs **begin_list);
int			object_error(char c);

/*		  	ERROR AND DEBUGGING			*/
int			error_out(int code);
int			check_all(rt_scene *sc);
int			exit_program(void);

/*			STR FUNCTIONS				*/
char		**ft_split(char const *s, char c);
size_t		ft_strlcat(char *dst, const char *src, size_t dstsize);
char		*ft_strchr(const char *s, int c);
char		*advance_through(char *this);
double		ft_strtod(const char *str);
void		*ft_calloc(size_t nmemb, size_t size);
char		*concat_here(char *str1, char *str2, int read);
void		ft_putstr_fd(char *s, int fd);
int			ft_strcmp(const char *s1, const char *s2);


/*			IMAGE FUNCTIONS				*/
int			put_it_on(rt_scene *scene_now, mlx_show *the_show);


#endif