/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stringutils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bfiquet <bfiquet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 13:09:12 by bfiquet           #+#    #+#             */
/*   Updated: 2025/04/17 14:17:29 by bfiquet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parser.h"
#include "../../libft/includes/libft.h"
#include <stdio.h>
#include <stdlib.h>

char	*ft_copy_substr(char *dest, char *substr_start, char *substr_end)
{
	char	*dest2;

	dest2 = dest;
	while (substr_start < substr_end)
		*dest++ = *substr_start++;
	*dest++ = 0;
	return (dest2);
}

char	*parser_accept(t_parser *parser, t_tokentype tokentype)
{
	char	*result_str;

	if (parser->tokenizer.type == UNFINISHED_QUOTE)
		return (parser->parser_error = MISSING_QUOTE, NULL);
	if (tokentype != parser->tokenizer.type)
		return (NULL);
	result_str = tokenizer_get_token(&parser->tokenizer,
			parser->tokenizer.remaining);
	if (parser->tokenizer.type == UNFINISHED_QUOTE)
		return (parser->parser_error = MISSING_QUOTE, NULL);
	if (!result_str)
		return (parser->parser_error = MEMORY_ALLOC, NULL);
	return (result_str);
}

char	*ft_strndup(const char *s, size_t size)
{
	char	*str;

	str = (char *)malloc(sizeof(*str) * size + 1);
	if (!str)
		return (NULL);
	ft_memcpy((char *)str, (const char *)s, size);
	str[size] = '\0';
	return (str);
}
