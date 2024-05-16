/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes_helper2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwurch <mwurch@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/05 15:28:56 by mwurch            #+#    #+#             */
/*   Updated: 2023/12/15 11:30:58 by mwurch           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

void	write_env_to_ret(char **s, char *ret, int *ret_index, t_envl *env);

void	process_normal_char(char **s, int *ret_index, char *ret, t_envl *env)
{
	if (ft_strchr(WHITESPACE, **s) && **s != env->sign)
	{
		ret[*ret_index] = **s;
		(*s)++;
		(*ret_index)++;
	}
	else if ((env->sign == 39 && **s == '$') || (**s == '$' 
			&& !ft_isalpha(*(*s + 1))))
	{
		ret[*ret_index] = **s;
		(*s)++;
		(*ret_index)++;
	}
	else
	{
		while (**s && !ft_strchr(WHITESPACE, **s) && **s != env->sign && \
		**s != '$')
		{
			ret[*ret_index] = **s;
			(*s)++;
			(*ret_index)++;
		}
	}
}

void	do_quoted_string(char **s, char *ret, int *ret_index, t_envl *env)
{
	while (**s && ft_strchr(QUOTESIGN, **s))
	{
		env->sign = **s;
		(*s)++;
		while (**s && **s != env->sign)
		{
			if ((**s == '$' && ft_isalpha(*(*s + 1))) && env->sign == '"')
				write_env_to_ret(s, ret, ret_index, env);
			else
				process_normal_char(s, ret_index, ret, env);
		}
		(*s)++;
	}
}

void	write_env_to_ret(char **s, char *ret, int *ret_index, t_envl *env)
{
	t_env	*tmp;

	tmp = env->envlist;
	(*s)++;
	while (tmp != NULL)
	{
		if (!my_strncmp(*s, tmp->var, ft_strlen(tmp->var)))
		{
			write_ret(ret, ret_index, tmp->value);
			while (*s && !ft_strchr(WHITESPACE, **s)
				&& **s != '$' && **s != 39 && **s != env->sign)
				(*s)++;
			break ;
		}
		tmp = tmp->next;
	}
	if (*(*s - 1) == '$')
		while (**s && !ft_strchr(WHITESPACE, **s) && **s != '$'
			&& **s != env->sign && **s != 39)
			(*s)++;
}

void	do_normal_dollar_sign(char **s, char *ret, int *ret_index, t_envl *env)
{
	t_env	*tmp;

	tmp = env->envlist;
	(*s)++;
	while (tmp != NULL)
	{
		if (!my_strncmp(*s, tmp->var, ft_strlen(tmp->var)))
		{
			write_ret(ret, ret_index, tmp->value);
			while (*s && !ft_strchr(WHITESPACE, **s)
				&& **s != '$' && !ft_strchr(QUOTESIGN, **s))
				(*s)++;
			break ;
		}
		tmp = tmp->next;
	}
	if (*(*s - 1) == '$')
		while (**s && !ft_strchr(WHITESPACE, **s) && **s != '$'
			&& !ft_strchr(QUOTESIGN, **s))
			(*s)++;
}

void	proc_nonquoted(t_envl *env, char **s, int *count)
{
	while (**s && !ft_strchr(QUOTESIGN, **s) && !ft_strchr(WHITESPACE, **s))
	{
		if (**s == '$' && !ft_strchr(WHITESPACE, *(*s + 1)))
			process_dollar_sign_normal(env->envlist, s, count);
		else
		{
			(*count)++;
			(*s)++;
		}
	}
}
