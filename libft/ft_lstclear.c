/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwurch <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/12 17:18:02 by mwurch            #+#    #+#             */
/*   Updated: 2022/12/12 17:32:12 by mwurch           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*head;
	t_list	*tmp;

	head = *lst;
	while (head)
	{
		tmp = head->next;
		ft_lstdelone(head, del);
		head = tmp;
	}
	*lst = NULL;
}
