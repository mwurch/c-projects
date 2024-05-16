/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_list.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpodack <rpodack@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/05 15:02:55 by rpodack           #+#    #+#             */
/*   Updated: 2023/11/27 16:42:47 by rpodack          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

void	sort_env(char **env)
{
	int		flag;
	int		i;
	int		len;
	char	*tmp;

	flag = 0;
	i = 0;
	len = ft_len(env);
	while (env[i] && flag == 0)
	{
		flag = 1;
		i = 0;
		while (i < len - 1)
		{
			if (ft_strcmp(env[i], env[i + 1]) > 0)
			{
				tmp = env[i];
				env[i] = env[i + 1];
				env[i + 1] = tmp;
				flag = 0;
			}
			i++;
		}
		len--;
	}
}

void	del_node_(t_env *env_exp)
{
	t_env	*curr;

	curr = env_exp;
	while (curr)
	{
		if (ft_strcmp(curr->next->var, "_") == 0)
		{
			free_node(curr->next);
			free(curr->next);
			curr->next = NULL;
			return ;
		}
		curr = curr->next;
	}
}

void	shlvl(t_envl *env)
{
	increase_shlvl(env->envlist);
	increase_shlvl(env->env_exp);
}
