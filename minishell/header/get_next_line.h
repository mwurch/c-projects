/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwurch <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 08:09:17 by mwurch            #+#    #+#             */
/*   Updated: 2023/01/17 08:09:19 by mwurch           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <sys/types.h>
# include <fcntl.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 4
# endif

typedef struct s_list
{
	char				*content;
	struct s_list		*next;
}t_list;

char		*get_next_line(int fd);
void		my_get_line(char **line, t_list *storage);
void		add_to_storage(t_list **storage, char *buf, int read_bytes);
void		read_to_storage(t_list **storage, int fd);
void		clean_storage(t_list **storage);
int			has_nl(t_list *storage);
t_list		*get_last(t_list *storage);
size_t		ft_strlen(const char *s);
void		creat_line(char **line, t_list *storage);
void		free_storage(t_list *storage);

#endif
