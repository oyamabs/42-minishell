/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchampio <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 17:25:45 by tchampio          #+#    #+#             */
/*   Updated: 2025/04/29 17:25:46 by tchampio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/executing.h"

void	ft_close(int fd)
{
	if (fd >= 0)
		close(fd);
}

void	free_tab(char **tab)
{
	int	i;

	if (!tab)
		free(tab);
	else
	{
		i = 0;
		while (tab[i])
		{
			free(tab[i]);
			i++;
		}
		free(tab);
	}
}

void	init_values_parse_nodes(t_cmd **cmds, t_cmd **current,
				t_node **tmp, t_node *nodes)
{
	*cmds = NULL;
	*current = NULL;
	*tmp = nodes;
}
