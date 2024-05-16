/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwurch <mwurch@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/02 20:15:02 by mwurch            #+#    #+#             */
/*   Updated: 2023/11/05 15:36:18 by mwurch           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

static int	count_len(char const *s, char c)
{
	int	count;

	count = 0;
	while (*s != c && *s != '\0')
	{
		count++;
		s++;
	}
	return (count);
}

static int	count_w(char const *s, char c)
{
	int	count;

	count = 0;
	while (*s && *s == c)
		s++;
	while (*s)
	{
		while (*s && *s != c)
			s++;
		count++;
		if (*s != '\0')
		{
			while (*s == c)
				s++;
		}
	}
	return (count);
}

static int	allocate_split_array(char **ret, char *s, char c, int *index)
{
	ret[*index] = ft_substr(s, 0, count_len(s, c));
	if (!ret[*index])
	{
		while (*index - 1 >= 0)
		{
			free(ret[*index]);
			(*index)--;
		}
		free(ret);
		return (0);
	}
	return (1);
}

char	**ft_split(char const *s, char c)
{
	char	**ret;
	int		index;

	index = 0;
	if (!s)
		return (NULL);
	ret = ft_calloc(count_w(s, c) + 1, sizeof(char *));
	if (!ret)
		return (NULL);
	while (*s)
	{
		while (*s == c)
			s++;
		if (*s)
		{
			if (!(allocate_split_array(ret, (char *)s, c, &index)))
				return (NULL);
			index++;
		}
		while (*s != c && *s)
			s++;
	}
	return (ret);
}
