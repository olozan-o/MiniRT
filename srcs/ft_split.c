/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olozano- <olozano-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/07 17:15:23 by olozano-          #+#    #+#             */
/*   Updated: 2019/10/22 18:08:14 by olozano-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

static int	count_words(char *str, char c)
{
	int i;
	int words;
	int first;

	if (!str)
		return (-1);
	i = 0;
	first = 1;
	words = 0;
	while (str[i])
	{
		if (str[i] == c)
			first = 1;
		else
		{
			if (first)
				words++;
			first = 0;
		}
		i++;
	}
	return (words);
}

static char	**first_alloc(char const *s, char c)
{
	int		words;
	char	**res;

	words = count_words((char*)s, c);
	if (!(res = malloc(sizeof(char*) * (words + 1))))
		return (NULL);
	res[words] = NULL;
	return (res);
}

static int	size_word(char const *s, int i, char c)
{
	int j;

	j = 0;
	while (s[i + j] != c && s[i + j])
		j++;
	return (j);
}

char		**ft_split(char const *s, char c)
{
	int		i;
	int		j;
	int		words;
	char	**res;

	if (!s || !(res = first_alloc(s, c)))
		return (0);
	i = -1;
	words = 0;
	while (*(s + ++i))
		if (s[i] != c)
		{
			if (!(res[words] = malloc(sizeof(char) * (size_word(s, i, c) + 1))))
				return (NULL);
			j = 0;
			while (s[i + j] != c && s[i + j])
			{
				res[words][j] = s[i + j];
				j++;
			}
			res[words][j] = '\0';
			words++;
			i = i + j - 1;
		}
	return (res);
}
