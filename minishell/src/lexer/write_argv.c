/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write_argv.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpodack <rpodack@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/05 15:04:13 by rpodack           #+#    #+#             */
/*   Updated: 2023/11/05 15:04:13 by rpodack          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

int	process_quote_arg(char *s, char **argv, t_envl *env, int *i)
{
	argv[*i] = get_quote_str(s, env);
	if (!argv[*i])
	{
		(void)argv;
		return (-1);
	}
	(*i)++;
	return (0);
}

void	process_home_env_logic(char **argv, t_envl *env, int *i, char *s)
{
	char	*tmp;

	tmp = NULL;
	argv[*i] = get_home_env(env, s);
	tmp = getcwd(tmp, PATH_MAX);
	update_pwds(env, tmp, argv[*i]);
	free(tmp);
	(*i)++;
}

void	process_dollar_logic(char **argv, char *s, t_envl *env, int *i)
{
	char	*tmp;

	tmp = NULL;
	tmp = my_ft_substr(s, 0, cmd_length(s));
	argv[*i] = dollar_dollar_bill_yaa(tmp, env);
	free(tmp);
	(*i)++;
}

int	process_default_logic(char *s, char **argv, int *i, t_envl *env)
{
	(void)env;
	argv[*i] = my_ft_substr(s, 0, cmd_length(s));
	if (!argv[*i])
		return (-1);
	(*i)++;
	return (0);
}

int	process_arguments(char **argv, char **s, t_envl *env, int *i)
{
	if (**s && **s != '|')
	{
		if (check_quotes(*s))
		{
			if (process_quote_arg(*s, argv, env, i) == -1)
				return (-1);
		}
		else if (ft_strcmp(*s, "~") == 0 || ft_strncmp(*s, "~ ", 2) == 0 || \
				ft_strncmp(*s, "~/", 2) == 0)
			process_home_env_logic(argv, env, i, *s);
		else if (check_for_dollar(*s) != 0)
			process_dollar_logic(argv, *s, env, i);
		else
		{
			if (process_default_logic(*s, argv, i, env) == -1)
				return (-1);
		}
		goto_next_arg(s);
	}
	if (specialheardoccase(env, argv, i) != 0)
		return (-1);
	return (0);
}
