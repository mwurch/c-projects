/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar_util2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwurch <mwurch@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/15 11:26:57 by mwurch            #+#    #+#             */
/*   Updated: 2023/12/15 12:53:42 by mwurch           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

char	*expand_that(char *args, t_envl *env)
{
	char	*tmp;
	char	*ret;

	tmp = args;
	tmp++;
	ret = ft_itoa(*(env->exit));
	if (!ret)
		return (NULL);
	env->tmp = ret;
	ret = ft_strjoin(ret, tmp);
	if (!ret)
		return (NULL);
	free(env->tmp);
	free(args);
	return (ret);
}

char	*cream(char *str, t_envl *env)
{
	char	*var;
	char	**args;
	int		i;

	i = 0;
	var = NULL;
	if (ft_strcmp("$", str) == 0)
		return (ft_strdup(str));
	args = ft_split(str, '$');
	if (!args)
		return (NULL);
	if (str[0] != '$')
	{
		var = ft_strjoin(var, args[i]);
		if (!var)
			return (catch_error(args));
		i++;
	}
	var = go_through_args(args, env, var, i);
	if (!var)
		return (catch_error(args));
	free_twod_array(args);
	return (var);
}

char	*go_through_args(char **args, t_envl *env, char *var, int i)
{
	t_env	*curr;

	while (args[i])
	{
		curr = env->env_exp;
		var = process_filling(args, curr, var, i);
		if (!var)
		{
			if (check_for_question(args) != 0)
			{
				var = do_it(args, env, &i, var);
			}
			if (!var)
			{
				i++;
				continue ;
			}
		}
		i++;
	}
	if (!var)
		var = ft_calloc(sizeof(char), 1);
	return (var);
}
