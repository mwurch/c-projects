/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwurch <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/28 15:28:58 by mwurch            #+#    #+#             */
/*   Updated: 2022/11/28 15:29:03 by mwurch           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <stddef.h>
#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	unsigned char			*d;
	const unsigned char		*s;
	int						i;

	if (!dest || !src)
		return (NULL);
	i = 0;
	s = src;
	d = dest;
	if (s < d)
	{
		while (n--)
			d[n] = s[n];
		return (d);
	}
	while (n--)
	{
		d[i] = s[i];
		i++;
	}
	return (d);
}
