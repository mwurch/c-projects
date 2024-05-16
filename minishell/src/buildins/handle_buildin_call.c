/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_buildin_call.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpodack <rpodack@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/05 15:02:36 by rpodack           #+#    #+#             */
/*   Updated: 2023/12/09 18:58:20 by rpodack          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

int	check_for_buildins(t_exec *ecmd, t_envl *env)
{
	env->i = 0;
	if (env->flag_for_exit == 1 && ft_len(ecmd->argv) == 1)
	{
		printf("%i: command not found\n", *(env->exit));
		env->flag_for_exit = 0;
		*(env->exit) = 127;
		return (1);
	}
	env->builds = ft_split("env export unset cd echo exit pwd", ' ');
	if (!env->builds)
		return (1);
	while (env->builds[env->i])
	{
		if (ft_strcmp(ecmd->argv[0], env->builds[env->i]) == 0)
		{
			free_twod_array(env->builds);
			env->builds = NULL;
			call_build(ecmd, env);
			return (1);
		}
		env->i++;
	}
	free_twod_array(env->builds);
	env->builds = NULL;
	return (0);
}

void	call_build(t_exec *emcd, t_envl *env)
{
	int	lenargv;

	lenargv = count_argv(emcd->argv);
	if (ft_strcmp(emcd->argv[0], "env") == 0)
		ft_env(&env->envlist, emcd->argv, env);
	else if (ft_strcmp(emcd->argv[0], "export") == 0)
		ft_export(env, emcd->argv);
	else if (ft_strcmp(emcd->argv[0], "cd") == 0 && lenargv <= 2)
		ft_cd(emcd->argv[1], env);
	else if (ft_strcmp(emcd->argv[0], "echo") == 0)
		ft_echo(emcd->argv, env);
	else if (ft_strcmp(emcd->argv[0], "unset") == 0)
		ft_unset(env->envlist, env->env_exp, emcd->argv, env);
	else if (ft_strcmp(emcd->argv[0], "exit") == 0 && lenargv <= 2)
		ft_exit(emcd->argv[1], env);
	else if (ft_strcmp(emcd->argv[0], "pwd") == 0)
		ft_pwd(env);
	else
	{
		if (strcmp(emcd->argv[0], "exit") == 0)
			printf("exit\n");
		printf("minishell: %s: too many arguments\n", emcd->argv[0]);
	}
}

int	check_for_pipe(char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (line[i] == ';')
			printf("; in commandline\n");
		else if (line[i] == '|')
			return (0);
		i++;
	}
	return (1);
}

int	count_argv(char **argv)
{
	int	i;

	i = 0;
	while (argv[i])
		i++;
	return (i);
}
