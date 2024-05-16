/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpodack <rpodack@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/05 15:04:01 by rpodack           #+#    #+#             */
/*   Updated: 2023/11/05 15:04:01 by rpodack          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

int		check_for_redir(char *s);
void	go_to_redir(char **str);
char	get_token(char **str);
char	*get_filename(char **str);
t_node	*get_redirnode(t_node *cmd, char *fn, char mod);

int	check_for_redir(char *s)
{
	while (*s && !ft_strchr(TERMSIGN, *s) && !ft_strchr(QUOTESIGN, *s))
		s++;
	return (*s && ft_strchr(REDIRSIGN, *s));
}

void	go_to_redir(char **str)
{
	char	*s;

	s = *str;
	while (*s && !ft_strchr(REDIRSIGN, *s))
		s++;
	*str = s;
}

char	get_token(char **str)
{
	char	ret;
	char	*s;

	s = *str;
	go_to_redir(&s);
	if (*s == '<')
		ret = '<';
	else if (*s == '>')
		ret = '>';
	s++;
	if (*s == '>')
	{
		ret = '+';
		s++;
	}
	else if (*s == '<')
	{
		ret = '^';
		s++;
	}
	*str = s;
	return (ret);
}

char	*get_filename(char **str)
{
	char	*ret;
	char	*s;

	s = *str;
	skip_whitespace(&s);
	ret = my_ft_substr(s, 0, cmd_length(s));
	if (!ret)
		return (NULL);
	*str = s;
	return (ret);
}

t_node	*get_redirnode(t_node *cmd, char *fn, char mod)
{
	t_node	*ret;

	ret = NULL;
	if (mod == '<')
		ret = redirnode(cmd, fn, O_RDONLY, 0);
	else if (mod == '>')
		ret = redirnode(cmd, fn, O_WRONLY | O_CREAT | O_TRUNC, 1);
	else if (mod == '+')
		ret = redirnode(cmd, fn, O_WRONLY | O_CREAT | O_APPEND, 1);
	else if (mod == '^')
		ret = redirnode(cmd, fn, O_RDONLY, 0);
	return (ret);
}
