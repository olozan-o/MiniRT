/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oscarlo <oscarlo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/14 11:19:39 by olozano-          #+#    #+#             */
/*   Updated: 2021/04/13 11:22:17 by oscarlo          ###   ########.fr       */
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

char		*concat_here(char *str1, char *str2, int read)
{
	int		size1;
	int		size2;
	int		i;
	char	*together;

	size1 = ft_strlen(str1);
	size2 = ft_strlen(str2);
	if (read < size2)
		size2 = read;
	if (!(together = malloc(size1 + size2 + 1)))
		return (NULL);
	i = -1;
	while (++i < size1)
		together[i] = str1[i];
	i--;
	while (++i < size1 + size2)
		together[i] = str2[i - size1];
	together[i] = '\0';
	free(str1);
	//free(str2);
	return (together);
}

char		*advance_through(char *this)
{
	int	i;

	i = 0;
	while (this[i] && ((this[i] >= 9 && this[i] <= 13) || this[i]==32))
		i++;
	while (this[i] && ((this[i] >= '0' && this[i] <= '9') || this[i] == '.' || this[i] == '-'))
		i++;
	return (this + i + (this[i] == ','));
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
	while (str[++i] >= '0' && str[i] <= '9')
	{
		number = number + (double)(str[i] - '0') / aux;
		aux = aux * 10;
	}
	return ((double)number * sign);
}

void		ft_putstr_fd(char *s, int fd)
{
	int	size;

	size = 0;
	while (*(s + size))
		size++;
	write(fd, s, size);
}

int		ft_strcmp(const char *s1, const char *s2)
{
	size_t	i;

	if (!s1 || !s2)
		return (0);
	i = 0;
	while (s1[i] == s2[i]
		&& s1[i] && s2[i])
		i++;
	if ((unsigned char)s1[i] > (unsigned char)s2[i])
		return (1);
	else if ((unsigned char)s1[i] < (unsigned char)s2[i])
		return (-1);
	else
		return (0);
<<<<<<< HEAD
}
=======
}
>>>>>>> 6016ff846d7f16667c0c287812ba08e802dcbcd1
