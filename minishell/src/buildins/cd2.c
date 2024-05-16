/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd2.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpodack <rpodack@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/27 16:34:58 by rpodack           #+#    #+#             */
/*   Updated: 2023/11/27 16:34:59 by rpodack          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

char	*go_home(char *str, t_envl *env, char *curr_path, char *fut_path)
{
	if (!str)
		fut_path = ft_home_user(str, env);
	else if (ft_strcmp(str, "-") == 0)
		fut_path = go_to_oldpwd(env);
	else if (ft_strncmp(str, "..", 2) == 0)
		fut_path = gone_dir(fut_path, curr_path, str, env);
	else if (ft_strncmp(str, curr_path, env->j) == 0)
		fut_path = putabspath(fut_path, curr_path, str, env);
	else if (env->changed == 0)
	{
		if (chdir(str) != 0)
		{
			*(env->exit) = 1;
			printf("minishell: cd: %s: No such file or directory\n", str);
		}
		else
			*(env->exit) = 0;
		env->changed = 1;
	}
	if (!fut_path)
		return (NULL);
	return (fut_path);
}

char	*putabspath(char *fut_path, char *curr_path, char *str, t_envl *env)
{
	fut_path = ft_strjoin(curr_path, str);
	if (!fut_path)
		return (NULL);
	chdir(fut_path);
	env->changed = 1;
	return (fut_path);
}
