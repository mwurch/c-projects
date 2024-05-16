/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_exec.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpodack <rpodack@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/05 15:03:10 by rpodack           #+#    #+#             */
/*   Updated: 2023/11/27 16:10:53 by rpodack          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

void	wait_for_child_exit(t_envl *env, int pid, t_node *tree)
{
	free_tree(tree);
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

void	execve_error_handling(t_envl *env, t_node *tree, char **envdp)
{
	*(env->exit) = -1;
	perror("execve");
	free_tree(tree);
	free_env(env);
	free_twod_array(envdp);
	exit (4);
}

void	do_exec(t_exec *ecmd, t_envl *env, t_node *tree)
{
	int		pid;

	if (check_for_buildins(ecmd, env) == 0)
	{
		handle_sigint_ignore();
		pid = my_fork(env, tree);
		if (pid == 0)
			do_exec_util(ecmd, env, tree);
		else
			wait_for_child_exit(env, pid, tree);
	}
	else
		free_tree(tree);
}

void	do_exec_util(t_exec *ecmd, t_envl *env, t_node *tree)
{
	char	**envdp;

	handle_sigquit_default();
	handle_sigint_default();
	if (ecmd->argv[0][0] != '.' && ecmd->argv[0][0] != '/')
		ecmd->argv[0] = get_right_path(env, ecmd);
	if (ecmd->argv[0] != NULL)
	{
		envdp = recreate_env(env);
		if (execve(ecmd->argv[0], ecmd->argv, envdp) == -1)
			execve_error_handling(env, tree, envdp);
	}
	else
		get_right_path_error(env, tree);
}
