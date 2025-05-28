/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_exec.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchampio <tchampio@student.42lehavre.      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 13:45:34 by tchampio          #+#    #+#             */
/*   Updated: 2025/05/27 16:12:15 by tchampio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/executing.h"
#include "../../includes/minishell.h"
#include <signal.h>
#include <sys/wait.h>
#include <unistd.h>

/* Fonction pour exécuter un builtin */
static int	execute_builtin(t_cmd *cmd, t_mini *mini)
{
	int	status;

	if (handle_redirections(cmd, mini))
	{
		restore_std_fds(mini);
		return (1);
	}
	status = exec_builtin(cmd->cmd, mini, cmd);
	if (cmd->redirs)
		restore_std_fds(mini);
	return (status);
}

/* Fonction pour configurer les pipes entre les commandes */
int	execute_cmd(t_mini *mini, t_cmd *cmd, t_cmd *cmd_list)
{
	int	status;

	if (is_builtin(cmd->cmd[0]))
	{
		status = exec_builtin(cmd->cmd, mini, cmd);
		restore_std_fds(mini);
		if (cmd->redirs)
			_reset_redirs_child(mini);
		cleanup_child_resources(mini, cmd_list);
		exit(status);
	}
	else
	{
		signal(SIGQUIT, SIG_DFL);
		exec(mini, cmd->cmd);
		_reset_redirs_child(mini);
		cleanup_child_resources(mini, cmd_list);
		exit(127);
	}
	return (status);
}

static void	execute_child(t_cmd *cmd, t_cmd *cmd_list, t_mini *mini)
{
	mini->is_in_fork = true;
	connect_pipes(mini, cmd, cmd_list);
	close_all_pipes(cmd_list);
	if (handle_redirections(cmd, mini))
	{
		restore_std_fds(mini);
		if (is_builtin(cmd->cmd[0]))
			_reset_redirs_child(mini);
		cleanup_child_resources(mini, cmd_list);
		exit(1);
	}
	if (cmd->cmd && cmd->cmd[0])
		execute_cmd(mini, cmd, cmd_list);
	cleanup_child_resources(mini, cmd_list);
	exit(0);
}

int	execute_all(t_mini *mini, t_cmd *cmd_list)
{
	t_cmd	*cmd;

	cmd = cmd_list;
	while (cmd)
	{
		if (setup_pipes(cmd))
			return (close_all_pipes(cmd_list), 1);
		cmd->pid = fork();
		if (cmd->pid == -1)
			return (perror("fork"), close_all_pipes(cmd_list), 1);
		else if (cmd->pid == 0)
		{
			execute_child(cmd, cmd_list, mini);
			exit(1);
		}
		close_pipes(cmd);
		cmd = cmd->next;
	}
	close_all_pipes(cmd_list);
	return (0);
}

int	execute_commands(t_cmd *cmd_list, t_mini *mini)
{
	if (!cmd_list)
		return (0);
	g_signal = 0;
	if (!cmd_list->next && cmd_list->cmd && cmd_list->cmd[0]
		&& is_builtin(cmd_list->cmd[0]))
		return (mini->last_ret = execute_builtin(cmd_list, mini),
			free_cmd(cmd_list), mini->last_ret);
	if (execute_all(mini, cmd_list) == 1)
		return (1);
	wait_all_cmds(mini, cmd_list);
	return (free_cmd(cmd_list), mini->last_ret);
}
