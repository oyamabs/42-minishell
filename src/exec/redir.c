/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchampio <tchampio@student.42lehavre.      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 16:03:24 by tchampio          #+#    #+#             */
/*   Updated: 2025/05/27 16:04:09 by tchampio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	save_redirections(t_mini *mini)
{
	mini->fdin = dup(STDIN_FILENO);
	mini->fdout = dup(STDOUT_FILENO);
}

int	handle_in_redirections(int *fd, t_redir *redir)
{
	*fd = open(redir->filename, O_RDONLY);
	if (*fd == -1)
		return (perror(redir->filename), 1);
	if (dup2(*fd, STDIN_FILENO) == -1)
		return (ft_close(*fd), 1);
	ft_close(*fd);
	return (*fd);
}

int	handle_out_redirections(int *fd, t_redir *redir)
{
	if (redir->type == REDIR_OUT)
		*fd = open(redir->filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else if (redir->type == _REDIR_APPEND)
		*fd = open(redir->filename, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (*fd == -1)
		return (perror(redir->filename), 1);
	if (dup2(*fd, redir->fd) == -1)
		return (ft_close(*fd), 1);
	ft_close(*fd);
	return (*fd);
}

/* Fonction qui gère les redirections pour une commande */
int	handle_redirections(t_cmd *cmd, t_mini *mini)
{
	t_redir	*redir;
	int		fd;

	if (!cmd->redirs)
		return (0);
	if (is_builtin(cmd->cmd[0]))
		save_redirections(mini);
	if (mini->fdin == -1 || mini->fdout == -1)
		return (1);
	redir = cmd->redirs;
	while (redir)
	{
		if (redir->type == REDIR_IN || redir->type == _REDIR_HEREDOC)
			handle_in_redirections(&fd, redir);
		else if (redir->type == REDIR_OUT || redir->type == _REDIR_APPEND)
			handle_out_redirections(&fd, redir);
		redir = redir->next;
	}
	return (0);
}

/* Fonction pour restaurer les descripteurs de fichier standard */
void	restore_std_fds(t_mini *mini)
{
	if (mini->fdin >= 0)
	{
		dup2(mini->fdin, STDIN_FILENO);
		ft_close(mini->fdin);
		mini->fdin = -1;
	}
	if (mini->fdout >= 0)
	{
		dup2(mini->fdout, STDOUT_FILENO);
		ft_close(mini->fdout);
		mini->fdout = -1;
	}
}
