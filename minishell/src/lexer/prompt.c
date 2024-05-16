/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpodack <rpodack@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/05 15:03:49 by rpodack           #+#    #+#             */
/*   Updated: 2023/11/05 15:03:49 by rpodack          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

char	*my_strjoin(char *str1, char *str2)
{
	int		i;
	int		j;
	char	*ret;

	i = 0;
	j = 0;
	if (!str1)
	{
		str1 = malloc(1 * sizeof(char));
		str1[0] = '\0';
	}
	ret = malloc (sizeof(char) * (ft_strlen(str1) + ft_strlen(str2) + 1));
	while (str1[i])
	{
		ret[i] = str1[i];
		i++;
	}
	while (str2[j])
		ret[i++] = str2[j++];
	ret[i] = '\0';
	free(str1);
	return (ret);
}

char	*get_promt(void)
{
	char	path[PATH_MAX];
	char	*ret;

	ret = NULL;
	ret = my_strjoin(ret, "\033[32m");
	ret = my_strjoin(ret, getenv("USER"));
	ret = my_strjoin(ret, ":\033[35m");
	if (!getcwd(path, PATH_MAX))
	{
		chdir("/home");
		free(ret);
		return (NULL);
	}
	ret = my_strjoin(ret, getcwd(path, PATH_MAX));
	ret = my_strjoin(ret, "\033[0m");
	ret = my_strjoin(ret, "$");
	return (ret);
}
