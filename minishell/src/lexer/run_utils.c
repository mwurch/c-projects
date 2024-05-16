/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpodack <rpodack@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/05 15:04:06 by rpodack           #+#    #+#             */
/*   Updated: 2023/11/05 15:04:06 by rpodack          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

void	wait_child3(int *pid, t_envl *env)
{
	waitpid(*pid, NULL, 0);
	*pid = -1;
	if (access("/tmp/tmp.txt", F_OK) == 0)
		unlink("/tmp/tmp.txt");
	if (WIFEXITED(*(env->exit)))
		*(env->exit) = WEXITSTATUS(*(env->exit));
	else if (WIFSIGNALED(*(env->exit)))
		*(env->exit) = WTERMSIG(*(env->exit));
}

void	wait_child4(int *pid, t_envl *env)
{
	waitpid(*pid, NULL, 0);
	if (access("/tmp/tmp.txt", F_OK) == 0)
		unlink("/tmp/tmp.txt");
	if (WIFEXITED(*(env->exit)))
		*(env->exit) = WEXITSTATUS(*(env->exit));
	else if (WIFSIGNALED(*(env->exit)))
		*(env->exit) = WTERMSIG(*(env->exit));
}

void	do_redir(t_redir *node, t_envl *env, t_node *tree)
{
	int	fd;
	int	pid;

	fd = open(node->file, node->mode, 0777);
	if (fd == -1)
		free_after_open_error(env, tree);
	pid = my_fork(env, tree);
	if (pid == 0)
	{
		my_dup2(fd, node->fd, env, tree);
		if (node->cmd != NULL)
			runcmd(node->cmd, env, tree);
		else
			return ;
	}
	else
		wait_child3(&pid, env);
}

void	do_redir_inparent(t_redir *node, t_envl *env, t_node *tree)
{
	int	fd;
	int	pid;

	fd = open(node->file, node->mode, 0777);
	if (fd == -1)
	{
		if (free_after_open_error1(tree) == -1)
		{
			*(env->exit) = 1;
			return ;
		}
	}
	pid = my_fork1(tree);
	if (pid == 0)
	{
		my_dup21(fd, node->fd, tree);
		if (node->cmd != NULL)
			runcmd(node->cmd, env, tree);
		else
			exit(0);
	}
	else if (pid == -1)
		return ;
	else
		wait_child4(&pid, env);
}

char	**recreate_env(t_envl *env)
{
	int		len;
	int		i;
	char	**ret;
	t_env	*curr;

	len = ft_lstsize_e(env->envlist);
	ret = malloc(sizeof(char *) * (len + 1));
	if (!ret)
		return (NULL);
	ret[len] = NULL;
	i = 0;
	curr = env->envlist;
	while (i != len)
	{
		ret[i] = ft_strdup(curr->full_line);
		i++;
		curr = curr->next;
	}
	return (ret);
}
