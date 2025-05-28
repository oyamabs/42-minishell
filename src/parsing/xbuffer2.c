/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xbuffer2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchampio <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 17:26:25 by tchampio          #+#    #+#             */
/*   Updated: 2025/04/29 17:26:27 by tchampio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parser.h"
#include <stdlib.h>

t_xbuffer	*create_xbuffer(size_t capacity)
{
	t_xbuffer	*new_xbuffer;

	new_xbuffer = (t_xbuffer *)malloc(capacity + sizeof(t_xbuffer));
	if (!new_xbuffer)
		return (NULL);
	new_xbuffer->next_chunk = NULL;
	new_xbuffer->last_chunk = new_xbuffer;
	new_xbuffer->capacity = capacity;
	if (capacity < 32)
		capacity = 32;
	new_xbuffer->growth_size = capacity;
	new_xbuffer->used = 0;
	return (new_xbuffer);
}

void	delete_xbuffer(t_xbuffer *xbuffer)
{
	t_xbuffer	*next_chunk;

	while (xbuffer)
	{
		next_chunk = xbuffer->next_chunk;
		free(xbuffer);
		xbuffer = next_chunk;
	}
}
