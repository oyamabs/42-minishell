/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchampio <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 17:27:22 by tchampio          #+#    #+#             */
/*   Updated: 2025/05/19 16:00:56 by tchampio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/signals.h"
#include <readline/readline.h>
#include <readline/history.h>
#include <unistd.h>
#include <stdlib.h>

int	g_signal = 0;

void	clean_exit(t_node *nodes, char *cmd, t_mini *mini)
{
	if (nodes)
		clear_list(&nodes);
	if (cmd)
		free(cmd);
	if (mini->parser.tokenizer.buffer)
		delete_xbuffer(mini->parser.tokenizer.buffer);
	if (mini->envvars)
	{
		free_env(mini->envvars);
		free(mini->envvars);
	}
	ft_close(STDIN_FILENO);
	ft_close(STDOUT_FILENO);
}

static void	init_minishell(t_mini *mini, t_parser *parser, char **envp)
{
	ft_bzero(parser, sizeof(t_parser));
	parser->tokenizer.buffer = create_xbuffer(0);
	mini->parser.tokenizer.buffer = parser->tokenizer.buffer;
	mini->envvars = init_envvars(envp);
	mini->last_ret = 0;
	mini->has_command_typed = false;
	mini->fdin = STDIN_FILENO;
	mini->fdout = STDOUT_FILENO;
	mini->is_in_fork = false;
}

static void	minishell_loop(t_mini *mini, t_parser *parser)
{
	t_node	*nodes;
	char	*cmd;

	nodes = NULL;
	parser->list = NULL;
	while (1)
	{
		create_prompt(mini->envvars, &mini->prompt);
		init_signals();
		parser->parser_error = 0;
		cmd = readline(mini->prompt.prompt);
		if (!cmd)
			break ;
		if (g_signal == 1 || g_signal == 2)
			mini->last_ret = 130;
		add_to_history(HISTORY_FILENAME, cmd);
		nodes = parser_parse(parser, cmd, mini);
		mini->head = nodes;
		mini->parser = *parser;
		redir_and_exec(mini, nodes);
	}
	clean_exit(nodes, cmd, mini);
}

int	main(int argc, char **argv, char **envp)
{
	t_mini		mini;
	t_parser	parser;
	int			fd_history;

	(void)argc;
	(void)argv;
	init_minishell(&mini, &parser, envp);
	fd_history = init_history(HISTORY_FILENAME);
	close(fd_history);
	minishell_loop(&mini, &parser);
	return (0);
}
