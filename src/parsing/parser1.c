/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bfiquet <bfiquet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 12:39:03 by bfiquet           #+#    #+#             */
/*   Updated: 2025/04/28 14:16:34 by bfiquet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parser.h"
#include "../../libft/includes/libft.h"
#include <stdio.h>

char	*parser_test_opt_word_elts(t_parser *parser, char *in_str)
{
	char	*result_str;

	result_str = parser_test_word_elt(parser);
	if (parser->parser_error)
		return (NULL);
	if (!result_str)
		return (in_str);
	if (parser->tokenizer.has_spaces)
		return (result_str);
	if (parser->parser_error)
		return (NULL);
	result_str = parser_test_opt_word_elts(parser, result_str);
	if (!result_str)
		return (NULL);
	return (result_str);
}

char	*parser_test_word_elt(t_parser *parser)
{
	char	*result_str;
	t_node	*newnode;
	char	*dup;

	if (!parser->tokenizer.content)
		return (dup = NULL);
	dup = ft_strdup(parser->tokenizer.content);
	if (parser->tokenizer.type == 'w'
		|| parser->tokenizer.type == FINISHED_SINGLE_QUOTE
		|| parser->tokenizer.type == FINISHED_DOUBLE_QUOTE
		|| parser->tokenizer.type == PIPE
		|| parser->tokenizer.type == REDIR_APPEND
		|| parser->tokenizer.type == REDIR_HEREDOC
		|| parser->tokenizer.type == REDIR_INFILE
		|| parser->tokenizer.type == REDIR_OUTFILE)
	{
		newnode = create_node(parser->tokenizer.type,
				dup, parser->tokenizer.has_envvars);
		add_node(&parser->list, newnode);
		result_str = parser_accept(parser, parser->tokenizer.type);
		if (!result_str)
			return (NULL);
		return (result_str);
	}
	return (NULL);
}

char	*parser_test_opt_command_elts(t_parser *parser, char *in_str)
{
	char	*result_str;

	result_str = parser_test_command_elt(parser);
	if (parser->parser_error)
		return (NULL);
	if (!result_str)
		return (in_str);
	result_str = parser_test_opt_command_elts(parser, result_str);
	if (!result_str)
		return (NULL);
	return (result_str);
}

char	*parser_test_command_elt(t_parser *parser)
{
	char	*result_str;

	result_str = parser_test_word(parser);
	if (!result_str)
		return (NULL);
	return (result_str);
}

char	*parser_test_command(t_parser *parser)
{
	char	*result_str;

	result_str = parser_test_command_elt(parser);
	if (!result_str)
		return (NULL);
	result_str = parser_test_opt_command_elts(parser, result_str);
	if (!result_str)
		return (NULL);
	return (result_str);
}
