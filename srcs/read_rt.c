/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_rt.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olozano- <olozano-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/14 10:24:03 by olozano-          #+#    #+#             */
/*   Updated: 2020/01/14 14:09:38 by olozano-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mlx.h>
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

rt_scene	*process_everything(char *all, rt_scene	*this_scene)
{
	char	*iterator;
	char	*limit;
	char	*aux;

	iterator = all;
	limit = iterator;
	//SPLIT PAR LIGNES VIDES !!! "\n\n"


