/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwurch <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/28 16:20:05 by mwurch            #+#    #+#             */
/*   Updated: 2022/11/28 16:20:08 by mwurch           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <stddef.h>
#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	const unsigned char	*tmp;

	if (!s)
		return (NULL);
	tmp = s;
	while (n--)
	{
		if (*tmp == (unsigned char)c)
			return ((void *)tmp);
		tmp++;
	}
	return (NULL);
}
