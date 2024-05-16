/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_util2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwurch <mwurch@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/05 15:03:37 by rpodack           #+#    #+#             */
/*   Updated: 2023/12/15 11:29:15 by mwurch           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

void	set_to_null(t_node *cmd)
{
	t_node	*tmp;
	t_redir	*rcmd;

	tmp = cmd;
	if (tmp->type == 3)
		rcmd = (t_redir *) tmp;
	while (tmp->type == 3)
	{
		if (tmp->type == 3)
			rcmd = (t_redir *) tmp;
		if (rcmd->cmd->type == 3)
			tmp = rcmd->cmd;
		else
		{
			rcmd->cmd = NULL;
			return ;
		}
	}
}

t_node	*execpars(char **s, t_envl *env)
{
	t_node	*ret;
	t_exec	*cmd;

	ret = execnode();
	if (!ret)
		return (NULL);
	cmd = (t_exec *) ret;
	ret = redirpars(ret, *s);
	if (!ret)
		return (NULL);
	cmd->argv = get_argv(s, env);
	if (!cmd->argv && env->here_flag == 0)
	{
		free_tree(ret);
		return (NULL);
	}
	if (!cmd->argv && env->here_flag == 1)
	{
		set_to_null(ret);
		free(cmd);
		cmd = NULL;
		env->here_flag = 0;
		goto_next_arg(s);
	}
	return (ret);
}

t_node	*pipepars(char **s, t_envl *env)
{
	t_node	*cmd;

	cmd = execpars(s, env);
	if (!cmd)
		return (NULL);
	if (**s == '|')
	{
		(*s)++;
		cmd = pipenode(cmd, pipepars(s, env));
		if (!cmd)
			return (NULL);
	}
	return (cmd);
}

t_node	*parsestr(char **s, t_envl *env)
{
	t_node	*cmd;

	cmd = NULL;
	cmd = pipepars(s, env);
	if (!cmd)
		return (NULL);
	return (cmd);
}

t_node	*parser(char *str, t_envl *env)
{
	char	*curr;
	t_node	*cmd;

	curr = str;
	cmd = parsestr(&curr, env);
	if (!cmd)
		return (NULL);
	return (cmd);
}
