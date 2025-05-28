/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeutils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchampio <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 17:24:46 by tchampio          #+#    #+#             */
/*   Updated: 2025/05/27 16:04:40 by tchampio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/executing.h"

void	save_redirs(t_mini *mini)
{
	mini->fdin = dup(STDIN_FILENO);
	mini->fdout = dup(STDOUT_FILENO);
}

void	close_pipes(t_cmd *cmd)
{
	if (cmd->prev && cmd->prev->pipe_fd[0] != -1)
	{
		ft_close(cmd->prev->pipe_fd[0]);
		cmd->prev->pipe_fd[0] = -1;
	}
	if (cmd->pipe_fd[1] != -1)
	{
		ft_close(cmd->pipe_fd[1]);
		cmd->pipe_fd[1] = -1;
	}
}

void	connect_pipes(t_mini *mini, t_cmd *cmd, t_cmd *cmd_list)
{
	if (cmd->prev && cmd->prev->pipe_fd[0] != -1)
	{
		if (dup2(cmd->prev->pipe_fd[0], STDIN_FILENO) == -1)
		{
			perror("dup2");
			cleanup_child_resources(mini, cmd_list);
			exit(1);
		}
	}
	if (cmd->pipe_fd[1] != -1)
	{
		if (dup2(cmd->pipe_fd[1], STDOUT_FILENO) == -1)
		{
			perror("dup2");
			cleanup_child_resources(mini, cmd_list);
			exit(1);
		}
	}
}
