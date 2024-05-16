/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpodack <rpodack@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/27 16:35:26 by rpodack           #+#    #+#             */
/*   Updated: 2023/11/27 16:35:27 by rpodack          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

int	is_valid_entry(char *var)
{
	int	i;

	i = 0;
	if (ft_isalpha(var[i]) == 0)
	{
		printf("minisell: export: \'%s\': not a valid identifier\n", var);
		return (1);
	}
	i++;
	while (var[i])
	{
		if (var[i] == '=')
			return (0);
		i++;
	}
	return (1);
}

void	find_node_in_exp(t_env *env_exp, char *var, int lenvar)
{
	t_env	*curr;

	curr = env_exp;
	while (curr)
	{
		if (ft_strncmp(curr->var, var, lenvar) == 0)
		{
			update_value(var, curr, lenvar);
			return ;
		}
		curr = curr->next;
	}
}

void	insert_to_exp(t_env **env_exp, t_env *tmp2)
{
	t_env	*curr;
	t_env	*tmp;

	curr = *env_exp;
	tmp = *env_exp;
	if (ft_strcmp((*env_exp)->var, tmp2->var) > 0)
	{
		ft_lstadd_front_e(env_exp, tmp2);
		return ;
	}
	while (curr)
	{
		if (ft_strcmp(curr->var, tmp2->var) > 0)
		{
			tmp->next = tmp2;
			tmp2->next = curr;
			return ;
		}
		tmp = curr;
		curr = curr->next;
	}
	if (!tmp->next)
		ft_lstadd_back_e(env_exp, tmp2);
}
