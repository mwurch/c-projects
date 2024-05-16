/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   runcmd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpodack <rpodack@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/05 15:04:09 by rpodack           #+#    #+#             */
/*   Updated: 2023/11/05 15:04:09 by rpodack          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

void	exec_exec(t_node *cmd, t_envl *env, t_node *tree, t_exec *enode)
{
	enode = NULL;
	enode = (t_exec *) cmd;
	do_exec(enode, env, tree);
}

void	runcmd(t_node *cmd, t_envl *env, t_node *tree)
{
	int		p[2];
	int		exit_return;
	t_exec	*enode;
	t_pipe	*pnode;
	t_redir	*rnode;

	enode = NULL;
	if (cmd->type == PIPE)
	{
		pnode = (t_pipe *) cmd;
		do_pipe(p, pnode, env, tree);
		free_tree(tree);
	}
	else if (cmd->type == EXEC)
		exec_exec(cmd, env, tree, enode);
	else if (cmd->type == REDIR)
	{
		rnode = (t_redir *) cmd;
		do_redir(rnode, env, tree);
		free_tree(tree);
	}
	exit_return = *(env->exit);
	free_env(env);
	exit(exit_return);
}

void	runcmd_inparent(t_node *cmd, t_envl *env, t_node *tree)
{
	t_exec	*enode;
	t_redir	*rnode;

	if (cmd->type == EXEC)
	{
		enode = (t_exec *) cmd;
		do_exec_inparent(enode, env, tree);
	}
	else if (cmd->type == REDIR)
	{
		rnode = (t_redir *) cmd;
		do_redir_inparent(rnode, env, tree);
	}
}
