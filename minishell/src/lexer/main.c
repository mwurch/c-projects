/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpodack <rpodack@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/08 22:21:29 by rpodack           #+#    #+#             */
/*   Updated: 2023/09/08 22:21:29 by rpodack          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

volatile sig_atomic_t	g_signal_received = 0;

void	init_sig(void)
{
	struct sigaction	sig_nichts;
	struct sigaction	sig_c;

	sigemptyset(&sig_nichts.sa_mask);
	sig_nichts.sa_handler = SIG_IGN;
	sig_nichts.sa_flags = 0;
	sigaction(SIGQUIT, &sig_nichts, NULL);
	sigemptyset(&sig_c.sa_mask);
	sig_c.sa_handler = &ctrl_c;
	sig_c.sa_flags = 0;
	sigaction(SIGINT, &sig_c, NULL);
}

int	main(int argc, char *argv[], char *envi[])
{
	t_envl		*env;
	static int	ex;

	ex = 0;
	env = init(envi, &ex);
	if (!env)
		return (-1);
	init_sig();
	if (argc != 1)
	{
		printf("minishell: %s: No such file or directory", argv[1]);
		return (127);
	}
	while (1)
	{
		minishell(env);
		if (g_signal_received != 0)
		{
			*(env->exit) = 130;
			g_signal_received = 0;
			env->flag_for_ctrlc = 1;
		}
		init_sig();
	}
}

void	err_minishell(t_envl *env)
{
	if (!env->node && env->here_flag == 1)
	{
		env->here_flag = 0;
		free(env->line);
		free(env->prompt);
		return ;
	}
	if (!env->node && g_signal_received != 0)
	{
		*(env->exit) = 130;
		free(env->line);
		free(env->prompt);
		return ;
	}
	if (!env->node && g_signal_received == 0)
	{
		free(env->line);
		free(env->prompt);
		ft_putstr_fd("minishell-parser Error\n", 2);
		return ;
	}
}

void	handle_prompt(t_envl *env)
{
	if (env->flag_for_ctrlc == 0)
		env->prompt = get_promt();
	else
	{
		env->flag_for_ctrlc = 0;
		g_signal_received = 0;
		env->prompt = ft_calloc(sizeof(char), 1);
	}
}
