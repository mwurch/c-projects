/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write_argv_util.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwurch <mwurch@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/27 16:35:53 by rpodack           #+#    #+#             */
/*   Updated: 2023/12/08 15:03:39 by mwurch           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

int	check_for_dollar(char *s)
{
	while (*s && !ft_strchr(WHITESPACE, *s) && !ft_strchr(TERMSIGN, *s))
	{
		if (ft_strchr(DOLLARSIGN, *s))
			return (1);
		s++;
	}
	return (0);
}

int	specialheardoccase(t_envl *env, char **argv, int *i)
{
	if (*i == 0)
	{
		(void)argv;
		env->here_flag = 1;
		return (-1);
	}
	return (0);
}
