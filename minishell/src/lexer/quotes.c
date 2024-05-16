/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwurch <mwurch@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/05 15:03:54 by rpodack           #+#    #+#             */
/*   Updated: 2023/12/08 15:52:50 by mwurch           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

int	check_quotes(char *s)
{
	while (*s && !ft_strchr(WHITESPACE, *s) && !ft_strchr(TERMSIGN, *s))
	{
		if (ft_strchr(QUOTESIGN, *s))
			return (1);
		s++;
	}
	return (0);
}

int	my_strncmp(const char *s1, const char *s2, size_t n)
{
	while ((*s1 != '\0' || *s2 != '\0') && n--)
	{
		if (*s1 == *s2)
		{
			s1++;
			s2++;
		}
		else
			return ((unsigned char)*s1 - (unsigned char)*s2);
	}
	if (*s2 == '\0' && *s1 == '$')
		return (0);
	else if (*s2 == '\0' && (!ft_strchr(WHITESPACE, *s1) && \
	!ft_strchr(QUOTESIGN, *s1)))
		return ((unsigned char)*s1 - (unsigned char)*s2);
	return (0);
}

void	write_ret(char *ret, int *ret_index, char *str)
{
	int	str_index;

	str_index = 0;
	while (str[str_index])
	{
		ret[*ret_index] = str[str_index];
		*ret_index += 1;
		str_index++;
	}
}

void	process_normal_char1(char **s, int *ret_index, char *ret, t_envl *env)
{
	while (**s && !ft_strchr(WHITESPACE, **s) && **s != '"' 
		&& !ft_strchr(QUOTESIGN, **s))
	{
		if (**s == '$' && !ft_strchr(WHITESPACE, *(*s + 1)))
			do_normal_dollar_sign(s, ret, ret_index, env);
		else
		{
			ret[*ret_index] = **s;
			(*s)++;
			(*ret_index)++;
		}
	}
}

char	*get_quote_str(char *s, t_envl *env)
{
	char	*ret;
	int		ret_index;
	int		size;

	size = quote_str_len(s, env) + 1;
	if (size == 0)
	{
		ft_putstr_fd("Unclosed QUOTES: ", 2);
		return (NULL);
	}
	ret_index = 0;
	ret = ft_calloc(size, sizeof(char));
	if (!ret)
		return (NULL);
	while (*s && !ft_strchr(WHITESPACE, *s) && !ft_strchr(TERMSIGN, *s))
	{
		process_normal_char1(&s, &ret_index, ret, env);
		do_quoted_string(&s, ret, &ret_index, env);
	}
	return (ret);
}
