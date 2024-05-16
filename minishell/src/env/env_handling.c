/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_handling.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpodack <rpodack@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/05 15:02:50 by rpodack           #+#    #+#             */
/*   Updated: 2023/12/02 19:26:50 by rpodack          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

char	*copy_home(t_envl *env)
{
	t_env	*curr;

	curr = env->envlist;
	while (ft_strcmp(curr->var, "HOME") != 0)
	{
		curr = curr->next;
		if (!curr)
			return (NULL);
	}
	return (ft_strdup(curr->value));
}

void	increase_shlvl(t_env *env)
{
	t_env	*curr;
	int		shlvl;
	char	*tmp;

	shlvl = 0;
	curr = env;
	while (curr)
	{
		if (strcmp(curr->var, "SHLVL") == 0)
		{
			shlvl = ft_atoi(curr->value);
			break ;
		}
		curr = curr->next;
	}
	shlvl++;
	tmp = ft_itoa(shlvl);
	free(curr->value);
	curr->value = tmp;
	free(curr->full_line);
	curr->full_line = ft_strjoin(curr->var, "=");
	tmp = curr->full_line;
	curr->full_line = ft_strjoin(curr->full_line, curr->value);
	free(tmp);
}

t_envl	*init(char **envi, int *ex)
{
	t_envl	*env;

	env = malloc(sizeof(t_envl));
	if (!env)
		return (NULL);
	init_envlists(env, envi);
	if ((!env->envlist) || (!env->env_exp))
	{
		free_env(env);
		return (NULL);
	}
	del_node_(env->env_exp);
	shlvl(env);
	init_nullptr(env);
	init_ints(env);
	env->exit = ex;
	env->home = copy_home(env);
	if (!env->home)
	{
		ft_freelst(env->envlist);
		ft_freelst(env->env_exp);
		free(env);
		return (NULL);
	}
	return (env);
}

t_envl	*init_envlists(t_envl *env, char **envi)
{
	env->envlist = init_env(envi);
	if (!env->envlist)
	{
		free(env);
		return (NULL);
	}
	sort_env(envi);
	env->env_exp = init_env(envi);
	if (!env->env_exp)
	{
		ft_freelst(env->envlist);
		free(env);
		return (NULL);
	}
	return (env);
}

t_env	*init_env(char **env)
{
	t_env	*envlist;
	t_env	*tmp;
	int		i;

	envlist = ft_lstnew_e();
	if (!envlist)
		return (NULL);
	fill_list(env[0], envlist);
	i = 1;
	while (env[i])
	{
		tmp = malloc(sizeof(t_env));
		if (!tmp)
			return (NULL);
		tmp->next = NULL;
		ft_lstadd_back_e(&envlist, tmp);
		fill_list(env[i], tmp);
		i++;
	}
	return (envlist);
}
