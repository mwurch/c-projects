/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwurch <mwurch@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/05 15:02:14 by rpodack           #+#    #+#             */
/*   Updated: 2023/12/15 12:53:18 by mwurch           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

void	ft_echo(char **str, t_envl *env)
{
	int	i;
	int	flag;

	if (!str[1])
	{
		printf("\n");
		return ;
	}
	flag = flag_or_not(str[1]);
	i = 1;
	while (flag_or_not(str[i]) == 0)
	{
		i++;
		if (!str[i])
			return ;
	}
	print_echo(str, i, flag, env);
	if (flag == 1)
		printf("\n");
	*(env->exit) = 0;
}

void	print_echo(char **str, int i, int flag, t_envl *env)
{
	char	*tmp;
	int		count;

	count = 0;
	while (str[i])
	{
		if (ft_strcmp(str[i], "\0") == 0)
		{
			i++;
			continue ;
		}
		if (count >= 1)
		{
			tmp = str[i];
			str[i] = ft_strjoin(" ", str[i]);
			if (!str[i])
				return ;
			free(tmp);
		}
		count = print_out(flag, str[i], count, env);
		i++;
	}
}

int	print_out(int flag, char *str, int count, t_envl *env)
{
	(void)flag;
	if (env->flag_for_exit == 1)
		env->flag_for_exit = 0;
	if (!str)
		return (count);
	printf("%s", str);
	count++;
	return (count);
}

int	flag_or_not(char *str)
{
	int	i;

	i = 1;
	if (str[0] == '-')
	{
		while (str[i] == 'n')
			i++;
		if (str[i] == '\0')
			return (0);
	}
	return (1);
}
