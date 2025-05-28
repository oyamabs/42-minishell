/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bfiquet <bfiquet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 14:18:45 by bfiquet           #+#    #+#             */
/*   Updated: 2025/05/20 12:27:06 by bfiquet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parser.h"
#include "../../includes/executing.h"
#include <stdio.h>

static int	handle_double_quote(char *str, int *i)
{
	int	quotes;

	quotes = 1;
	(*i)++;
	while (str[*i] && str[*i] != '"')
		(*i)++;
	if (str[*i] == '"')
		quotes--;
	return (quotes == 0);
}

static int	handle_single_quote(char *str, int *i)
{
	int	quotes;

	quotes = 1;
	(*i)++;
	while (str[*i] && str[*i] != '\'')
		(*i)++;
	if (str[*i] == '\'')
		quotes--;
	return (quotes == 0);
}

static int	process_quotes(char *str, int *d, int *ret, int *i_last)
{
	int	quotes;
	int	i;

	i = 0;
	quotes = 0;
	while (str[i])
	{
		if (str[i] == '"')
		{
			*d = 1;
			quotes += !handle_double_quote(str, &i);
			*i_last = i;
		}
		else if (str[i] == '\'')
		{
			*d = 2;
			quotes += !handle_single_quote(str, &i);
			*i_last = i;
		}
		if (str[i])
			i++;
		if ((str[i] == ' ' || str[i] == '\t') && quotes == 0)
			break ;
	}
	return (*ret = i, quotes);
}

static char	*handle_quotes_next(t_tokenizer *tokenizer, char *str, int i)
{
	char	*before;
	char	*after;
	char	*quoted;
	size_t	str_len;

	str_len = ft_strlen(str);
	tokenizer->content = xbuffer_alloc(tokenizer->buffer, str_len + 1);
	before = ft_substr(str, 0, i);
	ft_strcpy(tokenizer->content, before);
	free(before);
	after = ft_substr(str, i + 1, str_len);
	tokenizer->remaining = xbuffer_alloc(tokenizer->buffer,
			ft_strlen(after) + 1);
	ft_strcpy(tokenizer->remaining, after);
	free(after);
	quoted = split_quotes(tokenizer->content, 0);
	if (!quoted)
		return (free(str), NULL);
	ft_strcpy(tokenizer->content, quoted);
	free(quoted);
	free(str);
	return (tokenizer->content);
}

char	*handle_quotes(t_tokenizer *tokenizer, char *in_str)
{
	char	*str;
	int		quotes;
	int		d;
	int		i_last;
	int		i;

	if (!in_str)
		return (NULL);
	str = ft_strdup(in_str);
	if (!str)
		return (NULL);
	quotes = process_quotes(str, &d, &i, &i_last);
	if (quotes == 1)
		return (free(str), tokenizer->type = UNFINISHED_QUOTE,
			printf("quote error\n"), NULL);
	if (d == 2)
		tokenizer->type = FINISHED_SINGLE_QUOTE;
	if (d == 1)
		tokenizer->type = FINISHED_DOUBLE_QUOTE;
	if (is_redir(str[i_last + 1]))
		i = i_last;
	else if (i_last >= 3 && (is_quote(str[i_last - 1])
			&& is_redir(str[i_last - 2])))
		i = i_last - 3;
	return (handle_quotes_next(tokenizer, str, i));
}
