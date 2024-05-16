/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpodack <rpodack@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/05 15:03:19 by rpodack           #+#    #+#             */
/*   Updated: 2023/11/10 16:27:06 by rpodack          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

void	free_twod_array(char **arr)
{
	int	i;

	i = 0;
	if (!arr && !(arr[i]))
		return ;
	while (arr[i])
	{
		free(arr[i]);
		i++;
	}
	if (arr)
		free(arr);
	arr = NULL;
}

void	ft_freelst(t_env *list)
{
	t_env	*tmp;

	if (!list)
		return ;
	while (list != NULL)
	{
		tmp = list->next;
		if (list->full_line)
			free(list->full_line);
		if (list->value)
			free(list->value);
		if (list->var)
			free(list->var);
		free(list);
		list = tmp;
	}
}

void	free_env(t_envl *env)
{
	if (env->envlist)
		ft_freelst(env->envlist);
	if (env->env_exp)
		ft_freelst(env->env_exp);
	if (env->home)
		free(env->home);
	if (env)
		free(env);
}

void	free_return(t_envl *env)
{
	free(env->curr_path);
	*(env->exit) = 1;
	return ;
}

char	*ft_return(char *var, t_env *curr)
{
	char	*tmp;

	free(var);
	tmp = ft_strdup(curr->value);
	return (tmp);
}
