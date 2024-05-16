/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpodack <rpodack@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/27 16:35:18 by rpodack           #+#    #+#             */
/*   Updated: 2023/11/27 16:35:19 by rpodack          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

void	init_value_line(int size, int i, char *var, t_env *tmp)
{
	int		j;

	j = 0;
	tmp->value = ft_calloc(sizeof(char), size + 1);
	if (!tmp->value)
		return ;
	while (var[i])
	{
		tmp->value[j] = var[i];
		i++;
		j++;
	}
}

int	does_var_exist(t_envl *env, char *var, int lenvar)
{
	t_env	*curr;
	int		lencheck;

	curr = env->envlist;
	while (curr)
	{
		lencheck = ft_strlen(curr->var);
		if (ft_strncmp(curr->var, var, lenvar) == 0 && lenvar == lencheck)
		{
			update_value(var, curr, lenvar);
			find_node_in_exp(env->env_exp, var, lenvar);
			return (1);
		}
		curr = curr->next;
	}
	return (0);
}

void	update_value(char *var, t_env *curr, int lenvar)
{
	int		lenvalue;
	int		i;

	lenvalue = ft_strlen(var) - lenvar;
	free(curr->full_line);
	curr->full_line = ft_strdup(var);
	if (!curr->full_line)
		return ;
	free(curr->value);
	curr->value = ft_calloc(sizeof(char), lenvalue + 1);
	if (!curr->value)
	{
		free(curr->full_line);
		curr->full_line = NULL;
		return ;
	}
	i = 0;
	while (var[i] != '=')
		i++;
	i++;
	update_value_util(i, var, curr);
}

void	update_value_util(int i, char *var, t_env *curr)
{
	int		j;

	j = 0;
	while (var[i])
	{
		curr->value[j] = var[i];
		i++;
		j++;
	}
}

int	ft_lenvar(char *var)
{
	int	i;

	i = 0;
	while (var[i] != '=' && var[i])
		i++;
	return (i);
}
