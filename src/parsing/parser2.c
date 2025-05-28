/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bfiquet <bfiquet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 12:39:40 by bfiquet           #+#    #+#             */
/*   Updated: 2025/05/15 12:21:33 by bfiquet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "../../includes/parser.h"
#include "../../includes/executing.h"

char	*parser_test_word(t_parser *parser)
{
	char	*result_str;

	result_str = parser_test_word_elt(parser);
	if (!result_str)
		return (NULL);
	if (parser->tokenizer.has_spaces)
		return (result_str);
	result_str = parser_test_opt_word_elts(parser, result_str);
	if (!result_str)
		return (NULL);
	return (result_str);
}

char	*parser_axiom_line(t_parser *parser)
{
	char	*result_str;

	result_str = parser_test_command(parser);
	if (!result_str)
		return (NULL);
	result_str = parser_accept(parser, EOL);
	return (result_str);
}

void	handle_quote_error(void)
{
	printf("quote error\n");
}

int	check_envvar(char *in_str)
{
	int	i;

	if (!in_str)
		return (0);
	i = 0;
	while (in_str[i])
	{
		if (in_str[i] == '$')
			return (1);
		i++;
	}
	return (0);
}

t_node	*parser_parse(t_parser *parser, char *in_str, t_mini *mini)
{
	t_node	*nodes;
	int		envvar;

	if (parser->list)
	{
		clear_list(&parser->list);
		parser->list = NULL;
	}
	envvar = check_envvar(in_str);
	if (envvar == 1)
	{
		parser->tokenizer.has_envvars = true;
		in_str = handle_envvars(in_str, mini);
	}
	else
		parser->tokenizer.has_envvars = false;
	tokenizer_get_token(&parser->tokenizer, in_str);
	parser_axiom_line(parser);
	if (in_str)
		free(in_str);
	if (parser->parser_error == MISSING_QUOTE)
		return (NULL);
	nodes = parser->list;
	return (nodes);
}
