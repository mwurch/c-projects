/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_pipe.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpodack <rpodack@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/05 15:03:13 by rpodack           #+#    #+#             */
/*   Updated: 2023/11/05 15:03:14 by rpodack          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

void	wait_for_children(int *p, int *pid, t_envl *env)
{
	close(p[0]);
	close(p[1]);
	waitpid(pid[0], (env->exit), 0);
	if (WIFEXITED(*(env->exit)))
		*(env->exit) = WEXITSTATUS(*(env->exit));
	else if (WIFSIGNALED(*(env->exit)))
		*(env->exit) = WTERMSIG(*(env->exit));
	waitpid(pid[1], (env->exit), 0);
	if (WIFEXITED(*(env->exit)))
		*(env->exit) = WEXITSTATUS(*(env->exit));
	else if (WIFSIGNALED(*(env->exit)))
		*(env->exit) = WTERMSIG(*(env->exit));
}

void	do_pipe(int *p, t_pipe *pnode, t_envl *env, t_node *tree)
{
	int	pid[2];

	if (pipe(p) == -1)
		error_after_pipe(env, tree);
	pid[0] = my_fork(env, tree);
	if (pid[0] == 0)
	{
		my_dup2(p[1], 1, env, tree);
		close(p[0]);
		close(p[1]);
		runcmd(pnode->left, env, tree);
	}
	pid[1] = my_fork(env, tree);
	if (pid[1] == 0)
	{
		my_dup2(p[0], 0, env, tree);
		close(p[0]);
		close(p[1]);
		runcmd(pnode->right, env, tree);
	}
	wait_for_children(p, pid, env);
}
