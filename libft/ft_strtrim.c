/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwurch <mwurch@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/05 11:42:54 by mwurch            #+#    #+#             */
/*   Updated: 2023/06/14 17:22:41 by mwurch           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include "libft.h"

static int	is_set(char c, const char *set)
{
	while (*set)
	{
		if (*set == c)
			return (1);
		set++;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	int		i;
	int		len;
	char	*ret;

	if (!s1)
		return (NULL);
	i = 0;
	while (is_set(s1[0], set) == 1 && *s1)
	{
		s1++;
	}
	len = ft_strlen(s1);
	while (is_set(s1[len -1], set) == 1 && len > 0)
	{
		i++;
		len--;
	}
	ret = ft_substr(s1, 0, (ft_strlen(s1) - i));
	if (!ret)
		return (NULL);
	return (ret);
}
