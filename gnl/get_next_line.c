/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwurch <mwurch@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 08:09:10 by mwurch            #+#    #+#             */
/*   Updated: 2023/10/18 16:33:28 by mwurch           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include "get_next_line.h"

char	*get_next_line(int fd)
{
	static t_list	*storage;
	char			*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	line = NULL;
	read_to_storage(&storage, fd);
	if (storage == NULL)
		return (NULL);
	my_get_line(&line, storage);
	clean_storage(&storage);
	if (line[0] == '\0')
	{
		free_storage(storage);
		storage = NULL;
		free(line);
		return (NULL);
	}
	return (line);
}

void	my_get_line(char **line, t_list *storage)
{
	int	i;
	int	j;

	if (storage == NULL)
		return ;
	creat_line(line, storage);
	if (*line == NULL)
		return ;
	j = 0;
	while (storage)
	{
		i = 0;
		while (storage->content[i])
		{
			if (storage->content[i] == '\n')
			{
				(*line)[j++] = storage->content[i];
				break ;
			}
			(*line)[j++] = storage->content[i++];
		}
		storage = storage->next;
	}
	(*line)[j] = '\0';
}

void	add_to_storage(t_list **storage, char *buf, int read_bytes)
{
	t_list	*new;
	t_list	*last;
	int		i;

	new = malloc(sizeof(t_list));
	if (!new)
		return ;
	new->next = NULL;
	new->content = malloc((read_bytes + 1) * sizeof(char));
	if (!new->content)
	{
		free(new);
		return ;
	}
	i = -1;
	while (buf[++i])
		new->content[i] = buf[i];
	new->content[i] = '\0';
	if (*storage == NULL)
	{
		*storage = new;
		return ;
	}
	last = get_last(*storage);
	last->next = new;
}

void	read_to_storage(t_list **storage, int fd)
{
	int		read_bytes;
	char	*buf;

	read_bytes = 1;
	while (!has_nl(*storage) && read_bytes != 0)
	{
		buf = malloc((BUFFER_SIZE + 1) * sizeof(char));
		if (!buf)
			return ;
		read_bytes = read(fd, buf, BUFFER_SIZE);
		if (read_bytes == -1 || (*storage == NULL && read_bytes == 0))
		{
			if ((*storage) && read_bytes == -1)
			{
				free_storage(*storage);
				*storage = NULL;
			}
			free(buf);
			return ;
		}
		buf[read_bytes] = '\0';
		add_to_storage(storage, buf, read_bytes);
		free(buf);
	}
}

void	clean_storage(t_list **storage)
{
	t_list	*new;
	t_list	*last;
	int		i;
	int		j;

	new = malloc(sizeof(t_list));
	if (!new || !storage)
		return ;
	new->next = NULL;
	last = get_last(*storage);
	i = 0;
	while (last->content[i] && last->content[i] != '\n')
		i++;
	if (last->content && last->content[i] == '\n')
		i++;
	new->content = malloc(((ft_strlen(last->content) - i) + 1) * sizeof(char));
	if (new->content == NULL)
		return ;
	j = 0;
	while (last->content[i])
		new->content[j++] = last->content[i++];
	new->content[j] = '\0';
	free_storage(*storage);
	if (check_special_case(j, new, storage))
		return ;
}
