/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ctrl.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpodack <rpodack@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/05 15:04:18 by rpodack           #+#    #+#             */
/*   Updated: 2023/11/25 18:21:43 by rpodack          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

void	ctrl_nichts(int sig)
{
	(void)sig;
	return ;
}

void	ctrl_d(t_envl *env)
{
	rl_clear_history();
	if (env->prompt != NULL)
		free(env->prompt);
	free_env(env);
	printf("exit\n");
	exit(1);
}

void	ctrl_c(int sig)
{
	if (sig == SIGINT)
	{
		rl_replace_line("", 0);
		rl_on_new_line();
		g_signal_received = 1;
		ioctl(STDOUT_FILENO, TIOCSTI, "\n");
	}
}

void	chld(int sig)
{
	(void)sig;
	while (waitpid(-1, NULL, WNOHANG) > 0)
	{
	}
}
