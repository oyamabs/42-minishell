/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bfiquet <bfiquet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 13:08:22 by bfiquet           #+#    #+#             */
/*   Updated: 2025/05/22 16:34:24 by tchampio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parser.h"
#include "../../includes/executing.h"
#include <stdio.h>

char	*handle_redirection(t_tokenizer *tokenizer, char **in_str,
			char **result_str)
{
	if (**in_str == '>' && *(*in_str + 1) == '>')
		tokenizer->type = REDIR_APPEND;
	else if (**in_str == '>' && *(*in_str + 1) != '>')
		tokenizer->type = REDIR_OUTFILE;
	else if (**in_str == '<' && *(*in_str + 1) == '<')
		tokenizer->type = REDIR_HEREDOC;
	else if (**in_str == '<' && *(*in_str + 1) != '<')
		tokenizer->type = REDIR_INFILE;
	tokenizer->content = xbuffer_alloc(tokenizer->buffer,
			(*in_str - *result_str) + 42);
	if (!tokenizer->content)
		return (NULL);
	ft_copy_substr(tokenizer->content, *result_str,
		*in_str + (tokenizer->type > 255) + 1);
	*in_str += (tokenizer->type > 255) + 1;
	tokenizer->remaining = *in_str;
	return (*result_str);
}

char	*redirection_pipes(t_tokenizer *tokenizer, char **in_str,
			char **result_str)
{
	if ((**in_str == '>' || **in_str == '<') && tokenizer->type != 10023)
		return (handle_redirection(tokenizer, in_str, result_str));
	else if ((**in_str == '|') && tokenizer->type != 10023)
	{
		tokenizer->type = PIPE;
		tokenizer->content = xbuffer_alloc(tokenizer->buffer, 2);
		if (!tokenizer->content)
			return (NULL);
		ft_strlcpy(tokenizer->content, "|", 2);
		*in_str += 1;
		tokenizer->remaining = *in_str;
		return (tokenizer->content);
	}
	return (*result_str);
}

char	*handle_words(t_tokenizer *tokenizer, char *in_str, char *result_str)
{
	tokenizer->content = xbuffer_alloc(tokenizer->buffer,
			in_str - result_str + 1);
	if (!tokenizer->content)
		return (NULL);
	ft_copy_substr(tokenizer->content, result_str, in_str);
	tokenizer->type = 'w';
	tokenizer->remaining = in_str;
	return (result_str);
}

int	has_quotes(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (is_redir(str[i]))
			return (0);
		if (str[i] == ' ' || str[i] == '\t')
			return (0);
		if (str[i] == '\'' || str[i] == '"')
			return (1);
		i++;
	}
	return (0);
}

char	*tokenizer_get_token(t_tokenizer *tokenizer, char *in_str)
{
	char	*result_str;

	tokenizer->has_spaces = (*in_str == ' ' || *in_str == '\t');
	tokenizer->content = NULL;
	while (*in_str == ' ' || *in_str == '\t')
		in_str++;
	result_str = in_str;
	tokenizer->type = *in_str;
	if (*in_str == '>' || *in_str == '<' || *in_str == '|')
		return (redirection_pipes(tokenizer, &in_str, &result_str));
	if (has_quotes(in_str))
		return (result_str = handle_quotes(tokenizer, in_str));
	while (*in_str && *in_str != ' ' && *in_str != '\t'
		&& *in_str != '<' && *in_str != '>' && *in_str != '|')
		in_str++;
	if (result_str != in_str)
		return (handle_words(tokenizer, in_str, result_str));
	if (*in_str)
		tokenizer->remaining = ++in_str;
	else
		tokenizer->remaining = in_str;
	return (result_str);
}
