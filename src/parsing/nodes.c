/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nodes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchampio <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 17:26:12 by tchampio          #+#    #+#             */
/*   Updated: 2025/04/29 17:26:14 by tchampio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parser.h"
#include <stdlib.h>
#include <stdio.h>

t_node	*create_node(t_tokentype type, char *content, bool has_envvar)
{
	t_node	*node;

	node = malloc(sizeof(*node));
	if (!node)
		return (NULL);
	node->type = type;
	node->content = content;
	node->has_envvar = has_envvar;
	node->next = NULL;
	return (node);
}

void	add_node(t_node **list, t_node *new)
{
	t_node	*last;

	if (list)
	{
		if (*list)
		{
			last = *list;
			while (last->next != NULL)
				last = last->next;
			last->next = new;
		}
		else
			*list = new;
	}
}

void	clear_list(t_node **list)
{
	t_node	*next;

	if (!list || !*list)
		return ;
	while (list && *list)
	{
		next = (*list)->next;
		free((*list)->content);
		free(*list);
		*list = next;
	}
}

void	print_nodes(t_node *list)
{
	t_node	*current;

	if (!list)
	{
		printf("No list\n");
		return ;
	}
	current = list;
	while (current != NULL)
	{
		printf("Node { content: %s type: %d, envvars: %d next: %p }",
			current->content, current->type,
			current->has_envvar, current->next);
		if (current->next != NULL)
			printf(" -> ");
		else
			printf("\n");
		current = current->next;
	}
}
