/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olozano- <olozano-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/14 11:19:39 by olozano-          #+#    #+#             */
/*   Updated: 2020/01/14 14:02:25 by olozano-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

size_t	ft_strlen(const char *s)
{
	size_t count;

	if (!s)
		return (0);
	count = 0;
	while (s[count])
		count++;
	return (count);
}

char		*ft_strchr(const char *s, int c)
{
	char	*ret;

	ret = (char*)s;
	while (*ret != c)
	{
		if (*ret == '\0')
			return (0);
		ret++;
	}
	return (ret);
}

char		*concat_free(char *str1, char *str2)
{
	int		size1;
	int		size2;
	int		i;
	char	*together;

	size1 = ft_strlen(str1);
	size2 = ft_strlen(str2);
	if (!(together = malloc(size1 + size2 + 1)))
		return (NULL);
	i = 0;
	while (i < size1)
		together[i] = str1[i++];
	while (i < size1 + size2)
		together[i] = str2[i++ - size1];
	together[i] = '\0';
	free(str1);
	free(str2);
	return (together);
}

int			ft_atoi(const char *nptr)
{
	int				number;
	int				i;
	int				sign;

	i = 0;
	if (!nptr)
		return (0);
	while (nptr[i] == ' ' || (nptr[i] >= 9 && nptr[i] <= 13))
		i++;
	sign = 1;
	if (nptr[i] == '-' || nptr[i] == '+')
	{
		if (nptr[i] == '-')
			sign = -1;
		i++;
	}
	number = 0;
	while (nptr[i] >= '0' && nptr[i] <= '9')
	{
		number = number * 10 + (nptr[i] - '0');
		i++;
	}
	return (number * sign);
}