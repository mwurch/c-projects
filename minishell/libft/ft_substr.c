/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwurch <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/01 12:05:15 by mwurch            #+#    #+#             */
/*   Updated: 2022/12/01 12:05:16 by mwurch           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <stddef.h>
#include <stdlib.h>
#include "libft.h"

void	*check_sub(void)
{
	char	*dest;

	dest = malloc(sizeof(char) * 1);
	if (!dest)
		return (NULL);
	dest[0] = '\0';
	return (dest);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char			*dest;
	unsigned int	i;
	unsigned int	s_len;

	s_len = ft_strlen(s);
	i = 0;
	if (!s)
		return (NULL);
	if (len >= ft_strlen(s))
		len = ft_strlen(s) - start;
	if (ft_strlen(s) < start)
		return (check_sub());
	dest = (char *)malloc(sizeof(char) * (len + 1));
	if (!dest)
		return (NULL);
	if (start < s_len)
	{
		while (i < len && s[i] != '\0')
		{
			dest[i] = s[start + i];
			i++;
		}
	}
	dest[i] = '\0';
	return (dest);
}
