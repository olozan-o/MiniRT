/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_rt.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oscarlo <oscarlo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/14 10:24:03 by olozano-          #+#    #+#             */
/*   Updated: 2021/04/13 13:17:17 by oscarlo          ###   ########.fr       */
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
		resultat = concat_here(resultat, buffer, i_read);
	}
	free(buffer);
	if (i_read < 0)
		return (NULL); // ERROR READING = 2
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
			sc->height = (int)ft_strtod(advance_through(begin + 1));
		}
		return (0);
	}
	if (begin[0] == 'A')
	{
		if (sc->a_lum >= 0)
			return ((sc->a_lum = -444));
		else
			return (process_ambiance(sc, begin));
	}
	if (begin[0] == 'c' && begin[1] != 'y')
		return (process_camera(sc, begin));
	if (begin[0] == 'l')
		return (process_light(sc, begin));
	return (process_object(sc, begin));
}

int			process_everything(char *all, rt_scene *this_scene)
{
	int		i;
	char	**all_elements;

	all_elements = ft_split(all, '\n'); // IL FAUDRAIT PAS CHANGER POUR QUE CE SOIT UN SPLIT À PARTIR DE \n\n ??
	i = 0;
	while (all_elements[i])
	{
		write(1, "\n", 1); ft_putstr_fd(all_elements[i], 1);
		if (all_elements[i][0])
			if (process_element(this_scene, all_elements[i]) < 0)
				return (40); // ERROR > element not formatted correctly
		i++;
	}
	return (0);
	// negative values in this_scene mean doubles where there souldn't be
}
