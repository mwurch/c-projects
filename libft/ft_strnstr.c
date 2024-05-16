/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwurch <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/28 17:40:59 by mwurch            #+#    #+#             */
/*   Updated: 2022/11/28 17:41:02 by mwurch           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <stddef.h>
#include <stdio.h>
#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	i;
	size_t	little_len;

	little_len = ft_strlen(little);
	i = 0;
	if (*little == '\0')
		return ((char *) big);
	while (big[i] && i < len)
	{
		if (big[i] == little[0] && (len - i) >= little_len)
		{
			if (ft_strncmp((char *) &big[i], little, little_len) == 0)
				return ((char *) &big[i]);
		}
		i++;
	}
	return (NULL);
}
