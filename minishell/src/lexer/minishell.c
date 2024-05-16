/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpodack <rpodack@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/05 15:03:29 by rpodack           #+#    #+#             */
/*   Updated: 2023/12/02 18:32:35 by rpodack          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

int	check_line(t_envl *env)
{
	if (ft_strlen(env->line) == 0)
	{
		free(env->line);
		free(env->prompt);
		return (-1);
	}
	if (check_for_spaceonly_str(env->line))
	{
		free(env->line);
		free(env->prompt);
		return (-1);
	}
	return (0);
}

void	no_pipe(t_envl *env)
{
	add_history(env->line);
	free(env->line);
	env->line = NULL;
	free(env->prompt);
	env->prompt = NULL;
	runcmd_inparent(env->node, env, env->node);
	free_tree(env->node);
}

void	handle_pipe(t_envl *env)
{
	int	pid;

	add_history(env->line);
	free(env->line);
	free(env->prompt);
	pid = fork();
	if (pid == 0)
		runcmd(env->node, env, env->node);
	else
	{
		free_tree(env->node);
		waitpid(pid, (env->exit), 0);
		if (WIFEXITED(*(env->exit)))
			*(env->exit) = WEXITSTATUS(*(env->exit));
		else if (WIFSIGNALED(*(env->exit)))
			*(env->exit) = WTERMSIG(*(env->exit));
	}
}

int	check_for_spaceonly_str(char *s)
{
	while (*s && *s != '|')
	{
		if (!ft_strchr(" ", *s))
			return (0);
		s++;
	}
	return (1);
}

void	minishell(t_envl *env)
{
	handle_prompt(env);
	if (!env->prompt)
		return ;
	env->line = readline(env->prompt);
	env->flag_for_ctrlc = 0;
	if (g_signal_received != 0)
		*(env->exit) = 130;
	g_signal_received = 0;
	if (!env->line)
		ctrl_d(env);
	if (check_line(env) == -1)
		return ;
	env->node = parser(env->line, env);
	if (!env->node)
	{
		err_minishell(env);
		return ;
	}
	if (check_for_pipe(env->line) == 0)
		handle_pipe(env);
	else
		no_pipe(env);
	env->flag_for_ctrlc = 0;
	env->flag_for_exit = 0;
}
