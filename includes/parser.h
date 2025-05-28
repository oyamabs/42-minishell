/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bfiquet <bfiquet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 12:48:57 by freddy            #+#    #+#             */
/*   Updated: 2025/04/29 15:35:19 by bfiquet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include <stdbool.h>
# include <stddef.h>

typedef enum e_parse_error
{
	OK,
	GENERIC_SYNTAX,
	MEMORY_ALLOC,
	MISSING_PARENTHESIS,
	MISSING_QUOTE,
	MISSING_DQUOTE
}	t_parse_error;

typedef enum e_tokentype
{
	REDIR_INFILE = '<',
	REDIR_OUTFILE = '>',
	REDIR_HEREDOC = ('<' | ('<' << 8)),
	REDIR_APPEND = ('>' | ('>' << 8)),
	PIPE = '|',
	TERM_WORD = 'w',
	ASSIGN = '=',
	FINISHED_SINGLE_QUOTE = ('\'' | ('\'' << 8)),
	FINISHED_DOUBLE_QUOTE = ('\"' | ('\"' << 8)),
	UNFINISHED_QUOTE = '\'',
	EOL = '\0',
	ERROR = -1
}	t_tokentype;

typedef struct s_xbuffer
{
	struct s_xbuffer	*next_chunk;
	struct s_xbuffer	*last_chunk;
	size_t				growth_size;
	size_t				capacity;
	size_t				used;
}	t_xbuffer;

typedef struct s_tokenizer
{
	t_tokentype	type;
	char		*content;
	bool		has_spaces;
	bool		has_envvars;
	t_xbuffer	*buffer;
	char		*remaining;
}	t_tokenizer;

typedef struct s_node
{
	t_tokentype		type;
	char			*content;
	bool			has_envvar;
	struct s_node	*next;
}	t_node;

typedef struct s_parser
{
	t_tokenizer		tokenizer;
	t_parse_error	parser_error;
	t_node			*list;
}	t_parser;

char		*tokenizer_get_token(t_tokenizer *tokenizer, char *in_str);
char		*parser_accept(t_parser *parser, t_tokentype tokentype);
char		*parser_test_opt_word_elts(t_parser *parser, char *in_str);
char		*parser_test_word_elt(t_parser *parser);
char		*parser_test_opt_command_elts(t_parser *parser, char *in_str);
char		*parser_test_command_elt(t_parser *parser);
char		*parser_test_command(t_parser *parser);
char		*parser_test_word(t_parser *parser);
char		*parser_axiom_line(t_parser *parser);
t_xbuffer	*create_xbuffer(size_t capacity);
t_node		*create_node(t_tokentype type, char *content, bool has_envvar);
void		add_node(t_node **list, t_node *newnode);
void		clear_list(t_node **list);
void		print_nodes(t_node *list);
t_xbuffer	*create_xbuffer(size_t capacity);
void		delete_xbuffer(t_xbuffer *xbuffer);
void		*xbuffer_add_data(t_xbuffer *xbuffer, void *data, size_t size);
void		*xbuffer_alloc(t_xbuffer *xbuffer, size_t size);
size_t		xbuffer_size(t_xbuffer *xbuffer);
void		*xbuffer_copy_data(t_xbuffer *xbuffer, void *dest);
char		*ft_copy_substr(char *dest, char *substr_start, char *substr_end);
char		**args_from_nodes(t_node *nodes);
char		*handle_quotes(t_tokenizer *tokenizer, char *in_str);
#endif
