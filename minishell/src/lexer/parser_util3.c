/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_util3.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpodack <rpodack@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/05 15:03:39 by rpodack           #+#    #+#             */
/*   Updated: 2023/11/05 15:03:40 by rpodack          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

char	*create_tmp_file(char *del)
{
	size_t	del_len;
	int		fd;
	char	*ret;

	if (create_here_doc_file(&fd, del, &del_len, &ret) == -1)
		return (NULL);
	if (write_in_here_doc(fd, del_len, del, ret) == -1)
		return (NULL);
	return (ret);
}

char	*get_here_doc(char **str)
{
	char	*ret;
	char	*s;

	s = *str;
	skip_whitespace(&s);
	ret = create_tmp_file(s);
	if (!ret)
		return (NULL);
	*str = s;
	return (ret);
}
