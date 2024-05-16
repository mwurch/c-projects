/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_update_pwd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpodack <rpodack@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/05 15:02:09 by rpodack           #+#    #+#             */
/*   Updated: 2023/11/06 18:46:21 by rpodack          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

void	pwd_update(t_envl *env, char *fut_path)
{
	t_env	*curr;

	curr = env->envlist;
	while (ft_strcmp(curr->var, "PWD") != 0)
	{
		curr = curr->next;
		if (!curr)
			return ;
	}
	free(curr->full_line);
	curr->full_line = fill_new_full(curr);
	if (!curr->full_line)
	{
		free(curr->value);
		return ;
	}
	free(curr->value);
	curr->value = ft_strdup(fut_path);
}

void	oldpwd_update(t_envl *env, char *curr_path)
{
	t_env	*curr;

	curr = env->envlist;
	while (ft_strcmp(curr->var, "OLDPWD") != 0)
	{
		curr = curr->next;
		if (!curr)
			return ;
	}
	free(curr->full_line);
	curr->full_line = fill_new_full(curr);
	if (!curr->full_line)
	{
		free(curr->value);
		return ;
	}
	free(curr->value);
	curr->value = ft_strdup(curr_path);
}

void	update_pwds(t_envl *env, char *curr_path, char *fut_path)
{
	if (env->changed == 1)
		*(env->exit) = 0;
	else
		*(env->exit) = 1;
	pwd_update(env, fut_path);
	pwd_update(env, fut_path);
	oldpwd_update(env, curr_path);
	oldpwd_update(env, curr_path);
}

char	*go_to_oldpwd(t_envl *env)
{
	t_env	*curr;

	curr = env->envlist;
	while (strcmp(curr->var, "OLDPWD") != 0)
	{
		curr = curr->next;
		if (!curr)
		{
			printf("minishell: cd: OLDPWD not set\n");
			*(env->exit) = 1;
			return (NULL);
		}
	}
	chdir(curr->value);
	env->changed = 1;
	return (ft_strdup(curr->value));
}

char	*fill_new_full(t_env *curr)
{
	int		i;
	int		j;
	char	*new_full;

	i = ft_strlen(curr->var);
	j = ft_strlen(curr->value);
	new_full = ft_calloc(sizeof(char), (i + j) + 2);
	if (!new_full)
		return (NULL);
	i = 0;
	while (curr->var[i])
	{
		new_full[i] = curr->var[i];
		i++;
	}
	new_full[i] = '=';
	i++;
	j = 0;
	while (curr->value[j])
	{
		new_full[i] = curr->value[j];
		i++;
		j++;
	}
	return (new_full);
}
