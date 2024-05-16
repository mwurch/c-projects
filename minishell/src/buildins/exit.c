/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpodack <rpodack@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/05 15:02:30 by rpodack           #+#    #+#             */
/*   Updated: 2023/12/03 17:26:49 by rpodack          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

int		ft_isvalid_number(char *exitstatus);
void	exit_util(t_envl *env);

void	ft_exit(char *exitstatus, t_envl *env)
{
	int	status;

	if (!exitstatus)
	{
		exit_util(env);
		exit(0);
	}
	else if (ft_isvalid_number(exitstatus) == 0)
	{
		status = ft_atoi(exitstatus);
		exit_util(env);
		exit (status);
	}
	else
	{
		printf("exit\nminishell: exit: %s: numeric arguement required\n", \
		exitstatus);
	}
	exit (2);
}

void	exit_util(t_envl *env)
{
	if (env->line != NULL)
		free(env->line);
	if (env->prompt != NULL)
		free(env->prompt);
	if (env->node != NULL)
		free_tree(env->node);
	if (env->builds != NULL)
		free_twod_array(env->builds);
	free_env(env);
	rl_clear_history();
	printf("exit\n");
}

int	ft_isvalid_number(char *exitstatus)
{
	int	i;

	i = 0;
	while (exitstatus[i])
	{
		if (ft_isdigit(exitstatus[i]) == 0)
			return (1);
		i++;
	}
	return (0);
}
