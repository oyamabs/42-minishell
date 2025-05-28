/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executing.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchampio <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 17:24:16 by tchampio          #+#    #+#             */
/*   Updated: 2025/05/19 16:02:50 by tchampio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/executing.h"
#include "../../includes/parser.h"

int	is_builtin(char *cmd)
{
	if (ft_strncmp(cmd, "pwd", 4) == 0)
		return (1);
	if (ft_strncmp(cmd, "echo", 5) == 0)
		return (1);
	if (ft_strncmp(cmd, "cd", 3) == 0)
		return (1);
	if (ft_strncmp(cmd, "export", 7) == 0)
		return (1);
	if (ft_strncmp(cmd, "unset", 6) == 0)
		return (1);
	if (ft_strncmp(cmd, "env", 4) == 0)
		return (1);
	if (ft_strncmp(cmd, "exit", 5) == 0)
		return (1);
	return (0);
}

int	exec_builtin(char **cmd, t_mini *mini, t_cmd *_cmd)
{
	if (ft_strncmp(cmd[0], "pwd", ft_strlen(cmd[0])) == 0)
		mini->last_ret = ft_pwd();
	if (ft_strncmp(cmd[0], "echo", ft_strlen(cmd[0])) == 0)
		mini->last_ret = ft_echo(cmd, mini);
	if (ft_strncmp(cmd[0], "cd", ft_strlen(cmd[0])) == 0)
		mini->last_ret = ft_cd(mini, cmd);
	if (ft_strncmp(cmd[0], "export", ft_strlen(cmd[0])) == 0)
		mini->last_ret = ft_export(cmd, mini->envvars);
	if (ft_strncmp(cmd[0], "unset", ft_strlen(cmd[0])) == 0)
		mini->last_ret = ft_unset(cmd, mini->envvars);
	if (ft_strncmp(cmd[0], "env", ft_strlen(cmd[0])) == 0)
		mini->last_ret = ft_env(mini->envvars);
	if (ft_strncmp(cmd[0], "exit", ft_strlen(cmd[0])) == 0)
		mini->last_ret = ft_exit(cmd, mini, _cmd);
	return (0);
}

char	**cmd_tab(t_node *nodes)
{
	char	**tab;
	int		i;
	t_node	*start;

	start = nodes;
	i = 0;
	while (nodes)
	{
		i++;
		nodes = nodes->next;
	}
	tab = malloc(sizeof(char *) * (i + 1));
	if (!tab)
		return (NULL);
	i = 0;
	while (start)
	{
		tab[i] = ft_strdup(start->content);
		if (!tab[i])
			free_tab(tab);
		start = start->next;
		i++;
	}
	tab[i] = NULL;
	return (tab);
}

bool	check_for_void(t_cmd *cmds)
{
	t_cmd	*current;

	current = cmds;
	while (current)
	{
		if (!current->cmd || !current->cmd[0])
			return (false);
		current = current->next;
	}
	return (true);
}

void	redir_and_exec(t_mini *mini, t_node *nodes)
{
	t_cmd	*cmds;

	if (!nodes)
		return ;
	cmds = parse_nodes(mini, nodes);
	if (!cmds)
	{
		mini->last_ret = 2;
		return ;
	}
	if (!check_for_void(cmds))
	{
		printf("Empty command detected. Aborting.\n");
		free_cmd(cmds);
		mini->last_ret = 2;
		return ;
	}
	mini->has_command_typed = true;
	execute_commands(cmds, mini);
}
