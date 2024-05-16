/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwurch <mwurch@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/27 16:35:03 by rpodack           #+#    #+#             */
/*   Updated: 2023/12/15 12:53:37 by mwurch           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

char	*dollar_dollar_bill_yaa(char *str, t_envl *env)
{
	char	*var;

	var = NULL;
	env->flag_for_exit = 0;
	if (more_than_one(str) == 0)
		return (str);
	if (ft_strcmp(str, "$?") == 0)
	{
		env->flag_for_exit = 1;
		return (ft_itoa((*env->exit)));
	}
	if (more_than_one(str) > 0)
	{
		var = cream(str, env);
		return (var);
	}
	free(var);
	return (NULL);
}

char	*trim_dollar(char *str)
{
	int		len;
	char	*var;
	int		i;
	int		j;

	if (str[0] != '$')
		return (str);
	len = ft_strlen(str);
	var = ft_calloc(sizeof(char), len);
	if (!var)
		return (NULL);
	i = 1;
	j = 0;
	while (str[i])
	{
		var[j] = str[i];
		i++;
		j++;
	}
	return (var);
}

char	*catch_error(char **args)
{
	free_twod_array(args);
	return (NULL);
}

int	check_for_question(char **args)
{
	int	i;
	int	counter;

	counter = 0;
	i = 0;
	while (args[i])
	{
		if (args[i][0] == '?')
			counter++;
		i++;
	}
	return (counter);
}

char	*do_it(char **args, t_envl *env, int *i, char *var)
{
	env->temp = *i;
	while (args[env->temp])
	{
		if (args[env->temp][0] == '?')
		{
			args[env->temp] = expand_that(args[env->temp], env);
			if (!args[env->temp])
				return (catch_error(args));
		}
		(env->temp++);
	}
	env->temp = 0;
	while (args[env->temp])
	{
		env->tmp = var;
		var = ft_strjoin(var, args[env->temp]);
		if (!var)
			return (catch_error(args));
		free(env->tmp);
		env->temp++;
	}
	*i = env->temp - 1;
	return (var);
}
