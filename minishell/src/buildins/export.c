/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpodack <rpodack@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/05 15:02:33 by rpodack           #+#    #+#             */
/*   Updated: 2023/11/05 15:02:34 by rpodack          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../../header/minishell.h"

void	ft_export(t_envl *env, char **var)
{
	int	lenvar;
	int	i;

	if (!var[1])
		print_exp(env->env_exp);
	else
	{
		i = 1;
		while (var[i])
		{
			if (is_valid_entry(var[i]) != 0)
			{
				i++;
				continue ;
			}
			lenvar = ft_lenvar(var[i]);
			if (does_var_exist(env, var[i], lenvar) == 0)
				add_to_lists(env, var[i]);
			i++;
		}
	}
	*(env->exit) = 0;
}

void	print_exp(t_env *env_exp)
{
	t_env	*curr;

	curr = env_exp;
	while (curr)
	{
		printf("declare -x %s", curr->var);
		if (curr->value != NULL)
		{
			printf("=");
			printf("\"%s\"\n", curr->value);
		}
		else
			printf("\n");
		curr = curr->next;
	}
}

void	add_to_lists(t_envl *env, char *var)
{
	t_env	*tmp;

	tmp = malloc(sizeof(t_env));
	if (!tmp)
		return ;
	tmp->full_line = ft_strdup(var);
	if (!tmp->full_line)
	{
		free(tmp);
		return ;
	}
	init_other_lines(tmp, var);
	tmp->next = NULL;
	ft_lstadd_back_e(&env->envlist, tmp);
	add_to_env_exp(var, env);
}

void	add_to_env_exp(char *var, t_envl *env)
{
	t_env	*tmp2;

	tmp2 = malloc(sizeof(t_env));
	if (!tmp2)
		return ;
	tmp2->full_line = ft_strdup(var);
	if (!tmp2->full_line)
	{
		free(tmp2);
		return ;
	}
	init_other_lines(tmp2, var);
	tmp2->next = NULL;
	insert_to_exp(&env->env_exp, tmp2);
}

void	init_other_lines(t_env *tmp, char *var)
{
	int		lenfl;
	int		lenvar;
	int		i;

	lenfl = ft_strlen(var);
	lenvar = 0;
	while (var[lenvar] != '=' && var[lenvar] != '\0')
		lenvar++;
	tmp->var = ft_calloc(sizeof(char), lenvar + 1);
	if (!tmp->var)
		return ;
	i = 0;
	while (i != lenvar)
	{
		tmp->var[i] = var[i];
		i++;
	}
	i++;
	if (lenfl > lenvar)
		init_value_line(lenfl - lenvar, i, var, tmp);
}
