/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   accessutils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchampio <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 17:23:44 by tchampio          #+#    #+#             */
/*   Updated: 2025/05/19 12:30:04 by tchampio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/executing.h"

int	check_access(int right_to_check, char *filename)
{
	if (!access(filename, F_OK) && access(filename, right_to_check) == -1)
		return (-1);
	return (0);
}

int	try_open(t_redir *current)
{
	int	fd;

	fd = -1;
	if (current->type == REDIR_OUT)
	{
		if (check_access(W_OK, current->filename))
			return (printf("can't write file\n"), -1);
		fd = open(current->filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	}
	else if (current->type == _REDIR_APPEND)
	{
		if (check_access(W_OK, current->filename))
			return (printf("can't write file\n"), -1);
		fd = open(current->filename, O_WRONLY | O_CREAT | O_APPEND, 0644);
	}
	else if (current->type == REDIR_IN)
	{
		if (check_access(R_OK, current->filename))
			return (printf("can't read file\n"), -1);
		fd = open(current->filename, O_RDONLY);
	}
	else if (current->type == _REDIR_HEREDOC)
		fd = open(current->filename, O_RDONLY);
	return (fd);
}

void	reset_redirs_child(t_mini *mini)
{
	dup2(mini->fdin, STDIN_FILENO);
	ft_close(mini->fdin);
	close(STDIN_FILENO);
	mini->fdin = -1;
	close(STDOUT_FILENO);
	ft_close(mini->fdout);
	mini->fdout = -1;
}

void	clean_child(t_mini *mini, t_cmd *allcmds, int exit_code)
{
	reset_redirs_child(mini);
	free_env(mini->envvars);
	free(mini->envvars);
	delete_xbuffer(mini->parser.tokenizer.buffer);
	clear_list(&mini->head);
	free_cmd(allcmds);
	exit(exit_code);
}

void	clean_pipes(t_cmd *cmd, int *prev_fd)
{
	if (*prev_fd != -1)
		close(*prev_fd);
	if (cmd->next)
	{
		*prev_fd = cmd->pipe_fd[0];
		close(cmd->pipe_fd[1]);
	}
	else
		*prev_fd = -1;
}
