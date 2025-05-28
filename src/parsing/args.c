/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bfiquet <bfiquet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 09:58:29 by bfiquet           #+#    #+#             */
/*   Updated: 2025/05/19 10:50:23 by bfiquet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parser.h"
#include "../../libft/includes/libft.h"
#include <stdlib.h>
#include <stdio.h>

size_t	count_args(t_node *nodes)
{
	size_t	size;
	t_node	*current;

	if (!nodes)
		return (0);
	current = nodes;
	size = 0;
	while (current
		&& (current->type == TERM_WORD || current->type == FINISHED_DOUBLE_QUOTE
			|| current->type == FINISHED_SINGLE_QUOTE))
	{
		size++;
		current = current->next;
	}
	return (size);
}

char	**args_from_nodes(t_node *nodes)
{
	char	**args;
	t_node	*current;
	int		count;
	int		i;

	if (!nodes)
		return (NULL);
	count = count_args(nodes);
	args = malloc(sizeof(char *) * (count + 1));
	if (!args)
		return (NULL);
	current = nodes;
	i = 0;
	while (current
		&& (current->type == TERM_WORD || current->type == FINISHED_DOUBLE_QUOTE
			|| current->type == FINISHED_SINGLE_QUOTE))
	{
		args[i] = ft_strdup(current->content);
		i++;
		current = current->next;
	}
	args[i] = NULL;
	return (args);
}

int	is_redir(char c)
{
	if (c == '|' || c == '<' || c == '>')
		return (1);
	return (0);
}

int	is_quote(char c)
{
	if (c == '\'' || c == '"')
		return (1);
	return (0);
}
