/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwurch <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/02 16:14:21 by mwurch            #+#    #+#             */
/*   Updated: 2022/12/02 16:14:23 by mwurch           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <stdlib.h>
#include <stddef.h>
#include "libft.h"

static int	numlen_in_a(int n)
{
	int	count;

	count = 0;
	while (n)
	{
		count++;
		n = n / 10;
	}
	return (count);
}

static void	get_ascii_num(char *s, int *i, int n)
{
	if (n < 0)
	{
		n *= -1;
		s[*i] = '-';
		*i = *i + 1;
	}
	if (n > 9)
	{
		get_ascii_num(s, i, n / 10);
		n = n % 10;
	}
	if (n < 10)
	{
		s[*i] = n + '0';
		*i = *i + 1;
	}
}

char	*ft_itoa(int n)
{
	char	*ptr;
	int		i;
	int		len;

	if (n == -2147483648)
	{
		ptr = malloc(sizeof(char) * 12);
		if (!ptr)
			return (NULL);
		ft_strlcpy(ptr, "-2147483648", 12);
		return (ptr);
	}
	i = 0;
	len = numlen_in_a(n);
	if (n <= 0)
		ptr = malloc(len + 2);
	else
		ptr = malloc(len + 1);
	if (!ptr)
		return (NULL);
	get_ascii_num(ptr, &i, n);
	ptr[i] = '\0';
	return (ptr);
}
