/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpodack <rpodack@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/05 15:02:58 by rpodack           #+#    #+#             */
/*   Updated: 2023/11/05 15:02:59 by rpodack          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

t_env	*ft_lstnew_e(void)
{
	t_env	*newelement;

	newelement = malloc(sizeof(t_env));
	if (!newelement)
		return (NULL);
	newelement->next = NULL;
	return (newelement);
}

void	ft_lstadd_back_e(t_env **lst, t_env *new)
{
	t_env	*ptr;

	if (lst && *lst)
	{
		ptr = *lst;
		while (ptr->next)
			ptr = ptr -> next;
		ptr -> next = new;
	}
	else if (lst)
		*lst = new;
}

void	ft_lstadd_front_e(t_env **lst, t_env *new)
{
	if (!new)
		return ;
	if ((*lst) == NULL)
	{
		*lst = new;
		return ;
	}
	new->next = *lst;
	*lst = new;
}

t_env	*ft_lstlast_e(t_env *lst)
{
	if (!lst)
		return (NULL);
	while (lst->next)
		lst = lst->next;
	return (lst);
}

int	ft_lstsize_e(t_env *lst)
{
	int	i;

	i = 0;
	while (lst)
	{
		i++;
		lst = lst->next;
	}
	return (i);
}
