/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpodack <rpodack@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/05 15:03:16 by rpodack           #+#    #+#             */
/*   Updated: 2023/11/05 15:03:16 by rpodack          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

void	free_exec(t_exec *cmd)
{
	if (cmd->argv)
		free_twod_array(cmd->argv);
	free(cmd);
}

void	free_pipe(t_pipe *cmd)
{
	if (cmd->left)
		free_tree(cmd->left);
	if (cmd->right)
		free_tree(cmd->right);
	free(cmd);
}

void	free_redir(t_redir *cmd)
{
	free_tree(cmd->cmd);
	if (cmd->file)
		free(cmd->file);
	free(cmd);
}

void	free_tree(t_node *cmd)
{
	t_exec	*ecmd;
	t_pipe	*pcmd;
	t_redir	*rcmd;

	if (!cmd)
		return ;
	if (cmd->type == EXEC)
	{
		ecmd = (t_exec *) cmd;
		free_exec(ecmd);
	}
	else if (cmd->type == PIPE)
	{
		pcmd = (t_pipe *) cmd;
		free_pipe(pcmd);
	}
	else if (cmd->type == REDIR)
	{
		rcmd = (t_redir *) cmd;
		free_redir(rcmd);
	}
}

void	free_node(t_env *curr)
{
	free(curr->full_line);
	free(curr->var);
	free(curr->value);
}
