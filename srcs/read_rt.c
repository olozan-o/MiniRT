/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_rt.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olozano- <olozano-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/14 10:24:03 by olozano-          #+#    #+#             */
/*   Updated: 2020/01/15 19:44:42 by olozano-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

char	*read_everything(int fd)
{
	char	*resultat;
	char	*buffer;
	int		i_read;
	
	if (!(buffer = malloc (BUFFER_SIZE)))
		return (NULL);
	if (!(resultat = malloc (BUFFER_SIZE)))
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

int			process_element(rt_scene *sc, char *begin, int end)
{
	if (begin[0] == 'R')
	{
		if (sc->width > 0)
			sc->width = -444;
		else
		{
			sc->width = ft_atoi(begin + 1);
			sc->height = ft_atoi(begin + advance_through(begin, 1));
		}
	}
	if (begin[0] == 'A')
	{
		if (sc->a_lum >= 0)
			return ((sc->a_lum = -444));
		else
			return (process_ambiance(sc, begin, end));
	}
	if (begin[0] == 'c')
		return (process_camera(sc, begin, end));
	if (begin[0] == 'l')
		return (process_light(sc, begin, end));
	return (process_object(sc, begin, end));
}

int			*process_everything(char *all, rt_scene	*this_scene)
{
	int		i;
	int		inside;

	//SPLIT PAR LIGNES VIDES !!! "\n\n"
	i = 0;
	inside = 1;
	while (all[i + 1])
	{
		if (all[i] == '\n' && all[i + 1] == '\n')
		{
			if (inside)
			{
				// correctly formatted element ?
				if (!process_element(this_scene, all + inside, i - inside + 1))
					return(40);
				inside = 0;
			}
		}
		else if (all[i] != '\n' && !inside)
			inside = i;
		i++;
	}
	return (check_everything(this_scene));
	// negative values in this_scene mean doubles where there souldn't be
}



