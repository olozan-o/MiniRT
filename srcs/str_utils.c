/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olozano- <olozano-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/14 11:19:39 by olozano-          #+#    #+#             */
/*   Updated: 2020/01/14 13:26:47 by olozano-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t i;
	size_t j;
	size_t k;

	i = 0;
	j = 0;
	k = ft_strlen(src);
	while (dst[i] && i < dstsize)
		i++;
	if (!dst[i] && i < dstsize)
	{
		while (src[j] && j + i < dstsize - 1)
		{
			dst[i + j] = src[j];
			j++;
		}
		dst[i + j] = '\0';
	}
	return (i + k);
}

char		*ft_substrn(char const *str, int n)
{
	char *res;
	size_t i;

	if (!(res = malloc(n + 1)))
		return (NULL);
	i = 0;
	while (i < n)
	{
		res[i] = str[i];
		i++;
	}
	res[i] = '\0';
	return (res);
}
