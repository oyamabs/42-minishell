/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirutils2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchampio <tchampio@student.42lehavre.      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 16:06:42 by tchampio          #+#    #+#             */
/*   Updated: 2025/05/27 16:29:07 by tchampio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/executing.h"
#include <sys/wait.h>

void	_reset_redirs_child(t_mini *mini)
{
	ft_close(STDIN_FILENO);
	mini->fdin = -1;
	ft_close(STDOUT_FILENO);
	mini->fdout = -1;
}

int	setup_pipes(t_cmd *cmd)
{
	if (cmd->next)
	{
		if (pipe(cmd->pipe_fd) == -1)
		{
			perror("pipe");
			return (1);
		}
	}
	else
	{
		cmd->pipe_fd[0] = -1;
		cmd->pipe_fd[1] = -1;
	}
	return (0);
}

/* Fonction pour fermer tous les descripteurs de fichiers de pipe */
void	close_all_pipes(t_cmd *cmd_list)
{
	t_cmd	*cmd;

	cmd = cmd_list;
	while (cmd)
	{
		if (cmd->pipe_fd[0] != -1)
		{
			ft_close(cmd->pipe_fd[0]);
			cmd->pipe_fd[0] = -1;
		}
		if (cmd->pipe_fd[1] != -1)
		{
			ft_close(cmd->pipe_fd[1]);
			cmd->pipe_fd[1] = -1;
		}
		cmd = cmd->next;
	}
}

void	cleanup_child_resources(t_mini *mini, t_cmd *allcmds)
{
	free_cmd(allcmds);
	free_env(mini->envvars);
	free(mini->envvars);
	delete_xbuffer(mini->parser.tokenizer.buffer);
	clear_list(&mini->head);
}

void	wait_all_cmds(t_mini *mini, t_cmd *cmd_list)
{
	t_cmd	*cmd;
	int		status;

	cmd = cmd_list;
	while (cmd)
	{
		waitpid(cmd->pid, &status, 0);
		if (cmd->next == NULL)
		{
			if (_wifexited(status))
				mini->last_ret = _wexitstatus(status);
			else if (_wifsignaled(status))
				mini->last_ret = 128 + _wtermsig(status);
		}
		cmd = cmd->next;
	}
}
