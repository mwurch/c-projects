/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwurch <mwurch@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 08:09:28 by mwurch            #+#    #+#             */
/*   Updated: 2023/02/13 19:43:57 by mwurch           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include "get_next_line.h"
#include <stdio.h>

int		has_nl(t_list *storage);
t_list	*get_last(t_list *storage);
size_t	ft_strlen(const char *s);
void	creat_line(char **line, t_list *storage);
void	free_storage(t_list *storage);

int	has_nl(t_list *storage)
{
	int		i;
	t_list	*last;

	if (storage == NULL)
		return (0);
	last = get_last(storage);
	i = 0;
	while (last->content[i])
	{
		if (last->content[i] == '\n')
			return (1);
		i++;
	}
	return (0);
}

t_list	*get_last(t_list *storage)
{
	t_list	*current;

	current = storage;
	while (current && current->next)
		current = current->next;
	return (current);
}

size_t	ft_strlen(const char *s)
{
	int	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

void	creat_line(char **line, t_list *storage)
{
	int	i;
	int	len;

	len = 0;
	while (storage)
	{
		i = 0;
		while (storage->content[i])
		{
			if (storage->content[i] == '\n')
			{
				len++;
				break ;
			}
			i++;
			len++;
		}
		storage = storage->next;
	}
	*line = malloc(sizeof(char) * (len + 1));
}

void	free_storage(t_list *storage)
{
	t_list	*current;
	t_list	*next;

	current = storage;
	while (current)
	{
		free(current->content);
		next = current->next;
		free(current);
		current = next;
	}
}
