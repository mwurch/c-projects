/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes_helper.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpodack <rpodack@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/05 15:03:51 by rpodack           #+#    #+#             */
/*   Updated: 2023/11/05 15:03:51 by rpodack          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

void	increment_count(char **s, int *count)
{
	(*count)++;
	(*s)++;
}

void	process_dollar_sign(t_env *tmp, char **s, int *count, char sign)
{
	(*s)++;
	while (tmp != NULL)
	{
		if (!my_strncmp(*s, tmp->var, ft_strlen(tmp->var)))
		{
			*count += ft_strlen(tmp->value);
			while (**s && !ft_strchr(WHITESPACE, **s) && **s != sign \
			&& **s != '$' && **s != 39)
				(*s)++;
			break ;
		}
		tmp = tmp->next;
	}
	if (*(*s - 1) == '$')
		while (**s && !ft_strchr(WHITESPACE, **s) && **s != sign && \
		**s != '$' && **s != 39)
			(*s)++;
}

int	process_quoted_string(char **s, t_env *env, int *count, char sign)
{
	t_env	*tmp;

	tmp = env;
	while (**s && **s != sign)
	{
		if ((**s == '$' && ft_isalpha(*(*s + 1))) && sign == '"')
			process_dollar_sign(tmp, s, count, sign);
		else
			increment_count(s, count);
		tmp = env;
	}
	if (**s == '\0')
		return (-1);
	else
		return (0);
}

int	quote_str_len(char *s, t_envl *env)
{
	char	sign;
	int		count;

	count = 0;
	while (*s && !ft_strchr(WHITESPACE, *s) && !ft_strchr(TERMSIGN, *s))
	{
		proc_nonquoted(env, &s, &count);
		while (*s && ft_strchr(QUOTESIGN, *s))
		{
			sign = *s;
			s++;
			if (process_quoted_string(&s, env->envlist, &count, sign) == -1)
				return (-1);
			else
				s++;
		}
	}
	return (count);
}

void	process_dollar_sign_normal(t_env *env, char **s, int *count)
{
	t_env	*tmp;

	tmp = env;
	(*s)++;
	while (tmp != NULL)
	{
		if (!my_strncmp(*s, tmp->var, ft_strlen(tmp->var)))
		{
			*count += ft_strlen(tmp->value);
			while (**s && !ft_strchr(WHITESPACE, **s) \
			&& **s != '$' && !ft_strchr(QUOTESIGN, **s))
				(*s)++;
			break ;
		}
		tmp = tmp->next;
	}
	if (*(*s - 1) == '$')
		while (**s && !ft_strchr(WHITESPACE, **s) && \
		**s != '$' && !ft_strchr(QUOTESIGN, **s))
			(*s)++;
}
