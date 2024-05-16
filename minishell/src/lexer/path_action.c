/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_action.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpodack <rpodack@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/05 15:03:45 by rpodack           #+#    #+#             */
/*   Updated: 2023/12/02 19:10:01 by rpodack          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

char	*get_right_path(t_envl *env, t_exec *cmd)
{
	char	**paths;
	int		index;

	env->tmp = cmd->argv[0];
	cmd->argv[0] = ft_strjoin("/", cmd->argv[0]);
	if (!cmd->argv[0])
	{
		cmd->argv[0] = env->tmp;
		return (NULL);
	}
	free(env->tmp);
	env->ret = NULL;
	index = 0;
	paths = get_paths(env, cmd->argv[0]);
	while (paths[index] != NULL)
	{
		if (access(paths[index], R_OK | X_OK) == 0)
		{
			env->ret = ft_strdup(paths[index]);
			break ;
		}
		index++;
	}
	free_twod_array(paths);
	return (env->ret);
}

char	**get_paths(t_envl *env, char *cmd)
{
	int		index;
	char	**paths;

	env->curr = env->envlist;
	while (ft_strcmp(env->curr->var, "PATH") != 0)
		env->curr = env->curr->next;
	paths = ft_split(env->curr->value, ':');
	if (!paths)
		return (NULL);
	index = 0;
	while (paths[index] != NULL)
	{
		env->tmp = paths[index];
		paths[index] = ft_strjoin(paths[index], cmd);
		if (!paths[index])
		{
			paths[index] = env->tmp;
			free_twod_array(paths);
			return (NULL);
		}
		free(env->tmp);
		index++;
	}
	free(cmd);
	return (paths);
}
