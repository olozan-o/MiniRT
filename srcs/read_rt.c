/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_rt.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olozano- <olozano-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/14 10:24:03 by olozano-          #+#    #+#             */
/*   Updated: 2020/03/02 16:37:17 by olozano-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

char		*read_everything(int fd)
{
	char	*resultat;
	char	*buffer;
	int		i_read;

	if (!(buffer = malloc(BUFFER_SIZE)))
		return (NULL);
	if (!(resultat = malloc(BUFFER_SIZE)))
		return (NULL);
	resultat[0] = '\0';
	while ((i_read = read(fd, buffer, BUFFER_SIZE)))
	{
		resultat = together(resultat, buffer);
	}
	if (i_read < 0)
		return (error_out(2)); // ERROR READING = 2
	return (resultat);
}

int			process_element(rt_scene *sc, char *begin)
{
	if (begin[0] == 'R')
	{
		if (sc->width > 0)
			sc->width = -444;
		else
		{
			sc->width = (int)ft_strtod(begin + 1);
			sc->height = (int)ft_strtod(begin + advance_through(begin));
		}
	}
	if (begin[0] == 'A')
	{
		if (sc->a_lum >= 0)
			return ((sc->a_lum = -444));
		else
			return (process_ambiance(sc, begin));
	}
	if (begin[0] == 'c')
		return (process_camera(sc, begin));
	if (begin[0] == 'l')
		return (process_light(sc, begin));
	return (process_object(sc, begin));
}

int			*process_everything(char *all, rt_scene *this_scene)
{
	int		i;
	char	**all_elements;

	all_elements = ft_split(all, '\n');
	i = 0;
	while (all_elements[i])
	{
		if (all_elements[i][0])
			if (process_element(this_scene, all_elements[i]) < 0)
				return (40); // ERROR > element not formatted correctly
		i++;
	}
	return (check_everything(this_scene));
	// negative values in this_scene mean doubles where there souldn't be
}
