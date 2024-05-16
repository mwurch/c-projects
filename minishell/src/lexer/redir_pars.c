/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_pars.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpodack <rpodack@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/05 15:03:58 by rpodack           #+#    #+#             */
/*   Updated: 2023/11/05 15:03:58 by rpodack          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

t_node	*redirpars(t_node *cmd, char *s)
{
	t_node	*ret;
	char	mod;
	char	*filename;

	ret = cmd;
	while (check_for_redir(s))
	{
		mod = get_token(&s);
		if (process_filename(mod, &filename, s, cmd) == -1)
			return (NULL);
		ret = get_redirnode(cmd, filename, mod);
		if (!ret)
		{
			free_tree(cmd);
			return (NULL);
		}
		cmd = ret;
	}
	return (ret);
}

int	process_filename(char mod, char **filename, char *s, t_node *cmd)
{
	if (mod == '^')
		*filename = get_here_doc(&s);
	else
		*filename = get_filename(&s);
	if (!*filename)
	{
		free_tree(cmd);
		return (-1);
	}
	return (0);
}
