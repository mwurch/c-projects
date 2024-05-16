/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpodack <rpodack@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/05 15:03:22 by rpodack           #+#    #+#             */
/*   Updated: 2023/11/05 15:03:22 by rpodack          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

int	create_here_doc_file(int *fd, char *del, size_t *del_len, char **ret)
{
	*ret = ft_calloc(13, sizeof(char));
	if (!*ret)
		return (-1);
	ft_strlcpy(*ret, "/tmp/tmp.txt", 13);
	*fd = open(*ret, O_RDWR | O_CREAT, 0777);
	if (*fd == -1)
	{
		free(*ret);
		return (-1);
	}
	*del_len = cmd_length(del);
	return (0);
}

void	clean_up_here_doc(int fd, char *ret)
{
	close(fd);
	unlink(ret);
	free(ret);
}

int	write_in_here_doc(int fd, size_t del_len, char *del, char *ret)
{
	char	*buf;

	buf = get_next_line(0);
	if (!buf)
	{
		clean_up_here_doc(fd, ret);
		return (-1);
	}
	while (buf)
	{
		if (ft_strncmp(del, buf, del_len) == 0 && buf[del_len] == '\n')
			break ;
		write(fd, buf, ft_strlen(buf));
		free(buf);
		buf = get_next_line(0);
		if (!buf)
		{
			clean_up_here_doc(fd, ret);
			return (-1);
		}
	}
	free(buf);
	close(fd);
	return (0);
}
