/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar_util.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpodack <rpodack@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/27 16:35:10 by rpodack           #+#    #+#             */
/*   Updated: 2023/12/02 19:22:03 by rpodack          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

int	more_than_one(char *str)
{
	int	i;
	int	len;

	len = 0;
	i = 0;
	while (str[i])
	{
		if (str[i] == '$')
			len++;
		i++;
	}
	return (len);
}

size_t	ft_strlen_till_equal(char *args)
{
	size_t	len;

	len = 0;
	while (args[len] && args[len] != '=' && args[len] != ':'
		&& args[len] != '/')
		len++;
	return (len);
}

void	copy_over_append_rest(char *var, char *ret, \
char *args, int len_arg_to_delimiter)
{
	int		i;

	i = 0;
	while (var[i])
	{
		ret[i] = var[i];
		i++;
	}
	while (args[len_arg_to_delimiter])
	{
		ret[i] = args[len_arg_to_delimiter];
		i++;
		len_arg_to_delimiter++;
	}
}

char	*append_rest(char *var, char *args)
{
	int		len_arg_to_delimiter;
	int		len_to_add;
	char	*ret;

	len_arg_to_delimiter = ft_strlen_till_equal(args);
	len_to_add = ft_strlen(args) - ft_strlen_till_equal(args);
	ret = ft_calloc(sizeof(char), ft_strlen(var) + len_to_add + 1);
	if (!ret)
	{
		free(var);
		return (NULL);
	}
	copy_over_append_rest(var, ret, args, len_arg_to_delimiter);
	free(var);
	return (ret);
}

char	*process_filling(char **args, t_env *curr, char *var, int i)
{
	char	*tmp;

	while (ft_strncmp(args[i], curr->var, \
		ft_strlen_till_equal(args[i])) != 0 && curr != NULL)
	{
		curr = curr->next;
		if (!curr)
			break ;
	}
	if (curr)
	{
		tmp = var;
		var = ft_strjoin(var, curr->value);
		if (!var)
			return (catch_error(args));
		free(tmp);
	}
	if (ft_strlen_till_equal(args[i]) < ft_strlen(args[i]) && curr)
	{
		var = append_rest(var, args[i]);
		if (!var)
			return (catch_error(args));
	}
	return (var);
}
