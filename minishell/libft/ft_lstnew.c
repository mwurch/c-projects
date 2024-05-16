/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwurch <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/12 14:01:30 by mwurch            #+#    #+#             */
/*   Updated: 2022/12/12 14:01:31 by mwurch           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"
#include <stdlib.h>

t_list	*ft_lstnew(void *content)
{
	t_list	*tmp;

	tmp = (t_list *) malloc(sizeof(t_list));
	if (!tmp)
		return (NULL);
	tmp->content = content;
	tmp->next = NULL;
	return (tmp);
}
