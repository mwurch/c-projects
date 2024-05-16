/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpodack <rpodack@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/08 22:21:34 by rpodack           #+#    #+#             */
/*   Updated: 2023/09/08 22:21:34 by rpodack          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

void	skip_redir(char **str)
{
	char	*s;

	s = *str;
	while (*s && (*s == '<' || *s == '>'))
	{
		while (*s && (*s == '<' || *s == '>'))
			s++;
		while (*s && ft_strchr(WHITESPACE, *s))
			s++;
		while (*s && !ft_strchr(WHITESPACE, *s) && !ft_strchr(TERMSIGN, *s))
			s++;
		while (*s && ft_strchr(WHITESPACE, *s))
			s++;
	}
	*str = s;
}

int	cmd_and_flag_count(char *str)
{
	int		count;
	char	*s;

	s = str;
	count = 0;
	skip_whitespace(&s);
	while (*s && *s != '|')
	{
		if (*s == '<' || *s == '>')
			skip_redir(&s);
		if (*s && !ft_strchr(WHITESPACE, *s) && !ft_strchr(TERMSIGN, *s))
		{
			while (*s && !ft_strchr(WHITESPACE, *s) && !ft_strchr(TERMSIGN, *s))
				s++;
			count++;
		}
		skip_whitespace(&s);
	}
	return (count);
}

int	write_argv(char **argv, char **str, t_envl *env)
{
	int		i;
	char	*s;

	s = *str;
	i = 0;
	if (check_for_spaceonly_str(s))
		return (-1);
	skip_whitespace(&s);
	while (*s && *s != '|')
	{
		if (*s == '<' || *s == '>')
			skip_redir(&s);
		if (process_arguments(argv, &s, env, &i) == -1)
		{
			*str = s;
			return (-1);
		}
	}
	*str = s;
	return (0);
}

char	*get_home_env(t_envl *env, char *s)
{
	t_env	*curr;
	char	*tmp;

	curr = env->envlist;
	if (strncmp(s, "~/", 2) == 0)
	{
		s++;
		env->tmp = ft_strdup(env->home);
		tmp = env->tmp;
		env->tmp = ft_strjoin(env->tmp, s);
		free(tmp);
		return (env->tmp);
	}
	while (ft_strcmp(curr->var, "HOME") != 0 && curr->next != NULL)
	{
		curr = curr->next;
		if (!curr)
			break ;
	}
	if (ft_strcmp(curr->var, "HOME") == 0)
		return (ft_strdup(curr->value));
	else
		return (ft_home_user(NULL, env));
}

char	**get_argv(char **s, t_envl *env)
{
	char	**argv;
	int		argc;

	argc = cmd_and_flag_count(*s);
	argv = ft_calloc(argc + 1, sizeof(char *));
	if (!argv)
		return (NULL);
	if (write_argv(argv, s, env) == -1)
	{
		free_twod_array(argv);
		return (NULL);
	}
	if (argv[argc])
	{
		free(argv[argc]);
		argv[argc] = NULL;
	}
	return (argv);
}
