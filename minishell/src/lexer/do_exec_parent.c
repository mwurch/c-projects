/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_exec_parent.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpodack <rpodack@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/05 15:03:05 by rpodack           #+#    #+#             */
/*   Updated: 2023/12/02 19:09:47 by rpodack          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

void	execve_error_parent(t_node *tree, t_envl *env, char **envdp)
{
	perror("execve");
	free_tree(tree);
	free_env(env);
	free_twod_array(envdp);
	exit (4);
}

void	wait_for_child_in_paretn(t_envl *env, int pid)
{
	waitpid(pid, (env->exit), 0);
	if (WIFEXITED(*(env->exit)))
		*(env->exit) = WEXITSTATUS(*(env->exit));
	else if (WIFSIGNALED(*(env->exit)))
	{
		*(env->exit) = WTERMSIG(*(env->exit));
		if (*(env->exit) == SIGINT)
			ft_putstr_fd("\n", 2);
		if (*(env->exit) == SIGQUIT)
			ft_putstr_fd("Quit (core dumped)\n", 2);
		*(env->exit) = *(env->exit) + 128;
	}
}

void	call_execve(t_exec *ecmd, t_envl *env, t_node *tree, char	**envdp)
{
	handle_sigquit_default();
	handle_sigint_default();
	if (ecmd->argv[0][0] != '.' && ecmd->argv[0][0] != '/')
		ecmd->argv[0] = get_right_path(env, ecmd);
	if (ecmd->argv[0] != NULL)
	{
		envdp = recreate_env(env);
		if (execve(ecmd->argv[0], ecmd->argv, envdp) == -1)
			execve_error_parent(tree, env, envdp);
	}
	else
	{
		ecmd->argv[0] = malloc(1);
		if (!ecmd->argv[0])
			exit(127);
		perror("Command not found");
		free_tree(tree);
		free_env(env);
		exit(127);
	}
}

void	do_exec_inparent(t_exec *ecmd, t_envl *env, t_node *tree)
{
	int		pid;
	char	**envdp;

	envdp = NULL;
	if (check_for_buildins(ecmd, env) == 0)
	{
		handle_sigint_ignore();
		pid = my_fork(env, tree);
		if (pid == 0)
			call_execve(ecmd, env, tree, envdp);
		else
			wait_for_child_in_paretn(env, pid);
	}
}
