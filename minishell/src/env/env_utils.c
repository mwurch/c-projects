/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpodack <rpodack@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/08 22:22:16 by rpodack           #+#    #+#             */
/*   Updated: 2023/11/06 18:39:48 by rpodack          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

int	ft_strcmp(const char *s1, const char *s2)
{
	size_t	i;

	i = 0;
	if (!s1)
		return (-1);
	while (s1[i] || s2 [i])
	{
		if (s1[i] != s2[i])
			return ((unsigned char) s1[i] - (unsigned char) s2[i]);
		if (s2[i] == '\0' || s1[i] == '\0')
			return ((unsigned char) s1[i] - (unsigned char) s2[i]);
		i++;
	}
	return (0);
}

int	ft_len(char **env)
{
	int	i;

	i = 0;
	while (env[i])
		i++;
	return (i);
}

void	fill_list(char *env, t_env *tmp)
{
	int	i;

	tmp->full_line = ft_strdup(env);
	if (!tmp->full_line)
		return ;
	i = 0;
	while (env[i] != '=')
		i++;
	tmp->var = ft_calloc(sizeof(char), i + 1);
	if (!tmp->var)
	{
		free(tmp->full_line);
		return ;
	}
	i = 0;
	while (env[i] != '=')
	{
		tmp->var[i] = env[i];
		i++;
	}
	i++;
	init_value(env, i, tmp);
}

void	init_value(char *env, int i, t_env *tmp)
{
	int	j;
	int	len;

	len = ft_strlen(env);
	j = 0;
	while (env[i])
	{
		i++;
		j++;
	}
	i = len - j;
	tmp->value = ft_calloc(sizeof(char), j + 1);
	if (!tmp->value)
		return ;
	j = 0;
	while (env[i])
	{
		tmp->value[j] = env[i];
		j++;
		i++;
	}
}

void	init_nullptr(t_envl *env)
{
	env->line = NULL;
	env->prompt = NULL;
	env->builds = NULL;
	env->curr_path = NULL;
	env->fut_path = NULL;
	env->changed = 0;
}
