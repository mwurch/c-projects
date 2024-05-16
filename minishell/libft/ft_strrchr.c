/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwurch <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/28 14:52:50 by mwurch            #+#    #+#             */
/*   Updated: 2022/11/28 14:52:53 by mwurch           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <stddef.h>
#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	const char	*tmp;

	tmp = NULL;
	while (*s)
	{
		if (*s == (unsigned char)c)
			tmp = s;
		s++;
	}
	if (c == '\0')
		return ((char *)s);
	return ((char *) tmp);
}
