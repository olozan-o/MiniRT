/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olozano- <olozano-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/14 11:19:39 by olozano-          #+#    #+#             */
/*   Updated: 2020/03/02 16:34:12 by olozano-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

size_t		ft_strlen(const char *s)
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

int			advance_through(char *this)
{
	int	i;

	i = 0;
	while (this[i] && (this[i] >= 9 || this[i] <= 13))
		i++;
	while (this[i] && (this[i] >= '0' || this[i] <= '9' || this[i] <= '.'))
		i++;
	return (i + (this[i] != '\0'));
}

double		ft_strtod(const char *str)
{
	double	number;
	int		sign;
	int		i;
	int		aux;

	i = 0;
	while (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
		i++;
	sign = 1;
	if (str[i] == '-' || str[i] == '+')
		if (str[i++] == '-')
			sign = -1;
	number = 0;
	while (str[i] >= '0' && str[i] <= '9')
		number = number * 10 + (str[i++] - '0');
	if (str[i] != '.')
		return ((double)number * sign);
	aux = 10;
	while (str[i] >= '0' && str[i] <= '9')
	{
		number = number + (double)(str[i] - '0') / aux;
		aux = aux * 10;
		i++;
	}
	return ((double)number * sign);
}
