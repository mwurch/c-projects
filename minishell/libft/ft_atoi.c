/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwurch <mwurch@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/29 17:22:58 by mwurch            #+#    #+#             */
/*   Updated: 2023/11/05 15:39:46 by mwurch           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_atoi(const char *nptr)
{
	int	res;
	int	sign;

	res = 0;
	sign = 1;
	while (*(nptr) == '\r' || *(nptr) == '\n' || *(nptr) == '\t'
		|| *(nptr) == '\v' || *(nptr) == 32 || *(nptr) == '\f')
		nptr++;
	if (*nptr == '-')
	{
		sign *= -1;
		nptr++;
	}
	else if (*nptr == '+')
		nptr++;
	while (*nptr >= '0' && *nptr <= '9')
		res = res * 10 + (*(nptr++) - 48);
	return (res * sign);
}
