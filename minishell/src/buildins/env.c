/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpodack <rpodack@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/05 15:02:17 by rpodack           #+#    #+#             */
/*   Updated: 2023/11/05 20:15:45 by rpodack          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

void	ft_env(t_env **envlist, char **argv, t_envl *env)
{
	t_env	*last;
	t_env	*tmp;
	int		len;

	(void)env;
	len = count_argv(argv);
	if (len > 1)
	{
		printf("env: ‘%s’: No such file or directory\n", argv[1]);
		*(env->exit) = 127;
		return ;
	}
	tmp = print_env(*envlist);
	last = ft_lstlast_e(*envlist);
	if (tmp == last)
		*(env->exit) = 0;
	else
		*(env->exit) = 1;
}

t_env	*print_env(t_env *envlist)
{
	t_env	*curr;
	t_env	*tmp;

	curr = envlist;
	while (curr != NULL)
	{
		if (curr->next == NULL)
			tmp = curr;
		printf("%s\n", curr->full_line);
		curr = curr->next;
	}
	return (tmp);
}
