/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olozano- <olozano-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/14 12:31:02 by olozano-          #+#    #+#             */
/*   Updated: 2021/11/27 22:54:28 by olozano-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H

# define	MINIRT_H

# define	BUFFER_SIZE 128
# define	WIDTH 540
# define	HEIGHT 280
# define	ESC_KEY 65307
# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include "mlx.h"
# include <math.h>

typedef struct s_color
{
	int8_t			channel[4];
}					t_color;

typedef struct s_show
{
	void			*mlx_ptr;
	void			*win_ptr;
	void			*mlx_img;
	char			*data;
	int				bpp;
	int				size_line;
	int				endian;
}					t_mlx_show;

typedef	struct s_objs
{
	char			type;
	double			*coord;
	double			*orient;
	double			*params;
	double			*color;
	struct s_objs	*next;
}					rt_objs;

typedef	struct 		scene
{
	int				height;
	double			*up_v;
	double			**rot_m;
	int				width;
	double			a_lum;
	int				*a_color;
	rt_objs			*obj_list; // to be rechecked :: single or double pointers ??
	rt_objs			*camera; // to be rechecked :: single or double pointers ??
	rt_objs			*f_light;
}					rt_scene;

/*			PARSING FUNCTIONS			*/
char			*read_everything(int fd);
int				process_everything(char *all, rt_scene	*this_scene);
int				process_ambiance(rt_scene *sc, char *begin);
int				process_camera(rt_scene *sc, char *begin);
int				process_light(rt_scene *sc, char *begin);
int				process_object(rt_scene *sc, char *begin);

/*			INTERNAL STRUCT FUNCTIONS	*/
char			*get_some_d(double *things, int how_many, char *where_from);
rt_objs			*push_new_object(rt_objs **begin_list);
int				object_error(char c);

/*		  	ERROR AND DEBUGGING			*/
int				error_out(int code);
int				check_all(rt_scene *sc);
int				exit_program(char *str);
int				operate_key_press(int key);

/*			STR FUNCTIONS				*/
char			**ft_split(char const *s, char c);
size_t			ft_strlcat(char *dst, const char *src, size_t dstsize);
char			*ft_strchr(const char *s, int c);
char			*advance_through(char *this);
double			ft_strtod(const char *str);
void			*ft_calloc(size_t nmemb, size_t size);
char			*concat_here(char *str1, char *str2, int read);
void			ft_putstr_fd(char *s, int fd);
int				ft_strcmp(const char *s1, const char *s2);
int				ft_isspace(char c);
int				ft_strncmp(const char *s1, const char *s2, size_t n);

/*			MATH FUNCTIONS				*/
double     		*cross_product(double *one, double *other);
double     		*scalar_product(double *one, double *other);
double			single_product(double *one, double *other);
double      	*substract(double *one, double *other);
double      	*normalize(double *these3);
double 			**compute_rotation(double *orig, double *dir, double *up_v);
void			*world_to_cam(double *vec, double **rot_m);
double			*rotate_cam(double *origin, double *trans, double *up_v);

/*			IMAGE FUNCTIONS				*/
int				put_it_on(rt_scene *scene_now, t_mlx_show *the_show);


#endif