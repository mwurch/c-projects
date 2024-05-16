/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpodack <rpodack@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/08 22:21:20 by rpodack           #+#    #+#             */
/*   Updated: 2023/11/06 18:21:48 by rpodack          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

void	ft_cd(char *str, t_envl *env)
{
	env->changed = 0;
	env->curr_path = NULL;
	env->curr_path = getcwd(env->curr_path, PATH_MAX);
	if (!env->curr_path)
	{
		*(env->exit) = 1;
		return ;
	}
	env->j = ft_strlen(env->curr_path) + 1;
	env->fut_path = go_home(str, env, env->curr_path, env->fut_path);
	if (!env->fut_path)
		return (free_return(env));
	if (env->changed == 0)
	{
		if (!env->fut_path)
			env->fut_path = ft_strdup(str);
		if (!env->fut_path)
			return (free_return(env));
	}
	update_pwds(env, env->curr_path, env->fut_path);
	if (env->curr_path)
		free(env->curr_path);
	if (env->fut_path)
		free(env->fut_path);
	env->fut_path = NULL;
}

char	*my_getenv(char *str, t_envl *env)
{
	t_env	*curr;

	curr = env->envlist;
	while (curr)
	{
		if (ft_strcmp(curr->var, str) == 0)
			return (ft_strdup(curr->value));
		curr = curr->next;
	}
	return (NULL);
}

char	*ft_home_user(char *str, t_envl *env)
{
	char	*user;
	char	*ret;

	ret = NULL;
	user = NULL;
	ret = get_ret(env);
	if (!ret)
		return (NULL);
	user = ret;
	if (str && ret)
	{
		user = ft_strjoin(ret, str);
		if (!user)
		{
			free(ret);
			return (NULL);
		}
		free(ret);
	}
	chdir(user);
	env->changed = 1;
	return (user);
}

char	*get_ret(t_envl *env)
{
	char	*user;
	char	*home;
	char	*ret;

	home = ft_strdup("/home/");
	if (!home)
		return (NULL);
	user = my_getenv("USER", env);
	if (!user)
	{
		free(home);
		return (NULL);
	}
	ret = ft_strjoin(home, user);
	if (!ret)
	{
		free(home);
		free(user);
		return (NULL);
	}
	free(home);
	free(user);
	return (ret);
}

char	*gone_dir(char *fut_path, char *curr_path, char *str, t_envl *env)
{
	char	*tmp;

	fut_path = ft_strjoin(curr_path, "/");
	if (!fut_path)
		return (NULL);
	tmp = fut_path;
	fut_path = ft_strjoin(fut_path, str);
	if (!fut_path)
	{
		free(tmp);
		return (NULL);
	}
	free(tmp);
	chdir(fut_path);
	env->changed = 1;
	return (fut_path);
}
