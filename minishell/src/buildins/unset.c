/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpodack <rpodack@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/05 15:02:45 by rpodack           #+#    #+#             */
/*   Updated: 2023/12/02 19:27:09 by rpodack          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

int	is_entry_valid(char *to_unset)
{
	if (ft_isalpha(to_unset[0]) != 0)
		return (0);
	else
		return (1);
}

void	ft_unset(t_env *envlist, t_env *env_exp, char **to_unset, t_envl *env)
{
	int	i;

	(void)env;
	i = 1;
	while (to_unset[i])
	{
		if (is_entry_valid(to_unset[i]) != 0)
			printf("minishell: unset: \'%s\': not a valid identifier\n", \
			to_unset[i]);
		else
			search_and_destroy(to_unset[i], envlist, env_exp);
		i++;
	}
	*(env->exit) = 0;
}

void	search_and_destroy(char *to_unset, t_env *envlist, t_env *env_exp)
{
	t_env	*curr;

	curr = env_exp;
	while (ft_strcmp(to_unset, curr->next->var) != 0)
	{
		if (curr->next->next != NULL)
			curr = curr->next;
		else
			return ;
	}
	del_next_node(curr);
	curr = envlist;
	while (ft_strcmp(to_unset, curr->next->var) != 0)
		curr = curr->next;
	del_next_node(curr);
}

void	del_next_node(t_env *curr)
{
	t_env	*tmp;

	tmp = curr->next;
	curr->next = curr->next->next;
	free(tmp->full_line);
	free(tmp->value);
	free(tmp->var);
	free(tmp);
}

void	init_ints(t_envl *env)
{
	env->flag_for_exit = 0;
	env->flag_for_ctrlc = 0;
	env->here_flag = 0;
}
