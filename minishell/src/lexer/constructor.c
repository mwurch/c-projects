/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   constructor.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpodack <rpodack@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/05 15:03:02 by rpodack           #+#    #+#             */
/*   Updated: 2023/11/05 15:03:02 by rpodack          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

t_node	*pipenode(t_node *left, t_node *right)
{
	t_pipe	*node;

	if (!right)
	{
		free_tree(left);
		return (NULL);
	}
	node = ft_calloc(1, sizeof(t_pipe));
	if (!node)
	{
		free_tree(left);
		free_tree(right);
		return (NULL);
	}
	node->type = PIPE;
	node->left = left;
	node->right = right;
	return ((t_node *)node);
}

t_node	*execnode(void)
{
	t_exec	*node;

	node = ft_calloc(1, sizeof(t_exec));
	if (!node)
		return (NULL);
	node->type = EXEC;
	node->argv = NULL;
	return ((t_node *)node);
}

t_node	*redirnode(t_node *cmd, char *file, int mode, int fd)
{
	t_redir	*node;

	node = ft_calloc(1, sizeof(t_redir));
	if (!node)
		return (NULL);
	node->cmd = cmd;
	node->type = REDIR;
	node->file = file;
	node->fd = fd;
	node->mode = mode;
	return ((t_node *)node);
}
