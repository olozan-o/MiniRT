/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_elements1.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olozano- <olozano-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/15 19:29:11 by olozano-          #+#    #+#             */
/*   Updated: 2020/01/15 19:42:28 by olozano-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int		process_ambiance(rt_scene *sc, char *begin, int end)
{
	int i;

	i = 1;
	sc->a_lum = ft_atoi(begin + i);
	i = advance_through(begin + i, i);
	sc->a_color[0] = ft_atoi(begin + i);
	i = advance_through(begin + i, i);
	sc->a_color[0] = ft_atoi(begin + i);
	i = advance_through(begin + i, i);
	sc->a_color[0] = ft_atoi(begin + i);
	i = advance_through(begin + i, i);
		// HERE THE PROGRAM SHOULD OUTPUT THE APPROPRIATE ERROR MESSAGE
	if (i >= end)
		return (11);
	else 
		return (0);
}

