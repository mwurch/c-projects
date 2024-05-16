/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_util.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpodack <rpodack@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/08 22:21:39 by rpodack           #+#    #+#             */
/*   Updated: 2023/09/08 22:21:39 by rpodack          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

char	*my_ft_substr(char *str, int start, int end)
{
	char	*ret;

	if (!str)
		return (NULL);
	ret = malloc(((end - start) + 1) * sizeof(char));
	if (!ret)
		return (NULL);
	ret[end] = '\0';
	while (start < end && str[start] != '\0')
	{
		ret[start] = str[start];
		start++;
	}
	return (ret);
}

void	skip_whitespace(char **str)
{
	char	*s;

	s = *str;
	while (*s && ft_strchr(WHITESPACE, *s))
		s++;
	*str = s;
}

int	cmd_length(char *str)
{
	int	lenght;

	lenght = 0;
	while (str[lenght] && !ft_strchr(WHITESPACE, str[lenght]) && \
	!ft_strchr(TERMSIGN, str[lenght]))
		lenght++;
	return (lenght);
}

void	goto_next_arg(char **str)
{
	char	*s;

	s = *str;
	if (check_quotes(s))
		do_skipping(&s);
	else
		while (*s && !ft_strchr(WHITESPACE, *s) && !ft_strchr(TERMSIGN, *s))
			s++;
	skip_whitespace(&s);
	*str = s;
}

void	do_skipping(char **s)
{
	char	sign;

	sign = 0;
	while (**s && !ft_strchr(WHITESPACE, **s) && !ft_strchr(TERMSIGN, **s))
	{
		while (**s && !ft_strchr(QUOTESIGN, **s) && !ft_strchr(WHITESPACE, **s))
			(*s)++;
		while (**s && ft_strchr(QUOTESIGN, **s))
		{
			sign = **s;
			(*s)++;
			while (**s && **s != sign)
				(*s)++;
			(*s)++;
		}
	}
}
