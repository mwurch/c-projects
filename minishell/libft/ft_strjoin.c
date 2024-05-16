/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpodack <rpodack@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/02 13:55:26 by mwurch            #+#    #+#             */
/*   Updated: 2023/09/08 19:58:38 by rpodack          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

void	copy_over(char *s1, const char *s2, char *dst)
{
	while (*s1 != '\0')
		*dst++ = *s1++;
	while (*s2 != '\0')
		*dst++ = *s2++;
	*dst = '\0';
}

char	*ft_strjoin(char *s1, char const *s2)
{
	char	*dst;
	char	*cpy;
	int		f;

	f = 0;
	if (!s1)
	{
		s1 = ft_calloc(sizeof(char), 1);
		if (!s1)
			return (NULL);
		f = 1;
	}
	dst = (char *)malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (!dst)
		return (NULL);
	if (dst && s1 && s2)
	{
		cpy = dst;
		copy_over(s1, s2, dst);
	}
	else
		return (NULL);
	if (f == 1)
		free(s1);
	return (cpy);
}
/*
#include <stdio.h>
int	main()
{
	char s[50] = "Hallo";
	char p[] = "Marcel";
	
	
	printf("%s\n", ft_strjoin(s,p));
	printf("%s\n", s);
	printf("%s\n", p);
}*/
