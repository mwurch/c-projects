/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_functions.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpodack <rpodack@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/05 15:03:32 by rpodack           #+#    #+#             */
/*   Updated: 2023/11/05 20:34:06 by rpodack          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

int	my_fork(t_envl *env, t_node *tree)
{
	int	pid;

	pid = fork();
	if (pid == -1)
	{
		free_tree(tree);
		free_env(env);
		perror("fork() Error");
		exit(5);
	}
	else
		return (pid);
}

int	my_dup2(int old_fd, int new_fd, t_envl *env, t_node *tree)
{
	if (dup2(old_fd, new_fd) == -1)
	{
		free_tree(tree);
		free_env(env);
		perror("dup2() Error");
		exit(2);
	}
	return (new_fd);
}

void	free_after_open_error(t_envl *env, t_node *tree)
{
	free_tree(tree);
	free_env(env);
	perror("Failed to open file");
	exit(1);
}

void	get_right_path_error(t_envl *env, t_node *tree)
{
	perror("Command not found");
	free_tree(tree);
	free_env(env);
	exit(127);
}

void	error_after_pipe(t_envl *env, t_node *tree)
{
	free_tree(tree);
	free_env(env);
	perror("pipe() error");
	exit(11);
}
