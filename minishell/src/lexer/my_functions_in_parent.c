/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_functions_in_parent.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpodack <rpodack@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/27 16:32:53 by rpodack           #+#    #+#             */
/*   Updated: 2023/12/02 19:47:03 by rpodack          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

int	my_fork1(t_node *tree)
{
	int	pid;

	(void)tree;
	pid = fork();
	if (pid == -1)
	{
		perror("fork() Error");
		return (-1);
	}
	else
		return (pid);
}

int	my_dup21(int old_fd, int new_fd, t_node *tree)
{
	if (dup2(old_fd, new_fd) == -1)
	{
		free_tree(tree);
		perror("dup2() Error");
		exit(-1);
	}
	return (new_fd);
}

int	free_after_open_error1(t_node *tree)
{
	(void)tree;
	perror("Failed to open file");
	return (-1);
}
