/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bfiquet <bfiquet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 17:24:26 by tchampio          #+#    #+#             */
/*   Updated: 2025/05/19 14:13:41 by tchampio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/executing.h"
#include "../../includes/minishell.h"
#include <readline/readline.h>
#include <fcntl.h>
#include <unistd.h>

static char	*get_heredoc_filename(void)
{
	static int	id = 0;
	static char	*filename = NULL;
	char		*strid;

	filename = ft_calloc(sizeof(char)
			* ft_strlen("/tmp/minishell_heredocxxx") + 1, 1);
	if (!filename)
		return (NULL);
	strid = ft_itoa(id);
	if (!strid)
		return (free(filename), NULL);
	ft_strlcat(filename, "/tmp/minishell_heredoc",
		sizeof("/tmp/minishell_heredoc") + 4);
	ft_strlcat(filename, strid, sizeof("/tmp/minishell_heredoc") + 4);
	free(strid);
	id++;
	return (filename);
}

static int	create_tmp_file(char *filename)
{
	int	fd;

	fd = open(filename, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (fd == -1)
		perror("open failed");
	return (fd);
}

int	is_quotes(t_node *nodes)
{
	t_node	*current;
	int		quotes;

	quotes = 0;
	current = nodes;
	while (current)
	{
		if (is_redirection(current->type))
		{
			current = current->next;
			if (current->type == 10023 || current->type == 8738)
				quotes = 1;
			else
				quotes = 0;
			break ;
		}
		current = current->next;
	}
	return (quotes);
}

int	write_heredoc(t_mini *mini, char *limiter, int fd)
{
	size_t	lim_len;
	char	*dup;
	int		quotes;
	char	*line;

	lim_len = ft_strlen(limiter);
	quotes = is_quotes(mini->parser.list);
	dup2(mini->fdin, STDIN_FILENO);
	line = NULL;
	while (true)
	{
		free(line);
		line = readline("> ");
		if (quotes == 0 && check_envvar(line))
		{
			dup = handle_envvars(line, mini);
			free(line);
			line = dup;
		}
		if (!line || g_signal == 1 || !ft_strncmp(line, limiter, lim_len + 1))
			break ;
		ft_putstr_fd(line, fd);
		ft_putstr_fd("\n", fd);
	}
	return (free(line), 0);
}

int	handle_heredoc(t_mini *mini, char *limiter)
{
	int		fd;
	char	*filename;

	if (g_signal == 1 || g_signal == 2)
		return (-42);
	filename = get_heredoc_filename();
	fd = create_tmp_file(filename);
	if (fd == -1)
		return (printf("file error"));
	g_signal = 10;
	write_heredoc(mini, limiter, fd);
	if (g_signal == 1)
		mini->last_ret = 130;
	close(fd);
	if (fd == -1)
		return (printf("file error"));
	free(filename);
	return (fd);
}
