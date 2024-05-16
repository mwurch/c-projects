/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwurch <mwurch@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 16:23:30 by mwurch            #+#    #+#             */
/*   Updated: 2023/10/18 16:33:32 by mwurch           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include "get_next_line.h"

int	check_special_case(int j, t_list *new, t_list **storage)
{
	if (j == 0)
	{
		free(new->content);
		free(new);
		*storage = NULL;
		return (1);
	}
	*storage = new;
	return (0);
}
