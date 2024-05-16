/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwurch <mwurch@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/29 12:16:23 by mwurch            #+#    #+#             */
/*   Updated: 2023/11/05 15:35:37 by mwurch           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	unsigned char				*d;
	const unsigned char			*s;
	int							i;

	if (!dest && !src)
		return (NULL);
	i = 0;
	d = dest;
	s = src;
	while (n--)
	{
		d[i] = s[i];
		i++;
	}
	return (dest);
}
