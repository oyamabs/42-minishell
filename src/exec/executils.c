/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchampio <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 17:24:08 by tchampio          #+#    #+#             */
/*   Updated: 2025/05/14 14:36:47 by tchampio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/executing.h"
#include "../../includes/signals.h"
#include <fcntl.h>
#include <signal.h>
#include <stdio.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <unistd.h>

int	exec(t_mini *mini, char **nodes)
{
	int		i;
	char	**dir;
	char	*path;
	t_env	*env;

	if (g_signal == 1)
		return (130);
	env = search_env(mini->envvars, "PATH");
	if (!env || !*env->value)
		return (exec_cmd_without_path(mini, nodes), 0);
	dir = ft_split(env->value, ':');
	if (!dir || !dir[0])
		return (perror("Error: Invalid PATH"), -1);
	i = 0;
	path = NULL;
	while (dir[i] && !path)
		path = check_path(dir[i++], nodes[0]);
	if (!path)
		exec_cmd_without_path(mini, nodes);
	else
		exec_cmd_with_path(path, nodes, mini);
	free(path);
	free_tab(dir);
	return (mini->last_ret);
}

void	exec_cmd_without_path(t_mini *mini, char **nodes)
{
	char		**env_array;
	struct stat	stats;

	dup2(mini->fdout, STDOUT_FILENO);
	if (access(nodes[0], F_OK) == -1)
		return (mini->last_ret = 127,
			(void)ft_putstr_fd("Command not found 🫵😹\n", 2));
	if (access(nodes[0], X_OK) == -1)
		return (mini->last_ret = 127,
			(void)ft_putstr_fd("Permission denied 🫵😹\n", 2));
	if (stat(nodes[0], &stats) == 0)
		if (stats.st_mode & S_IFDIR)
			return (mini->last_ret = 126,
				(void)ft_putstr_fd("file is a directory 🫵😹\n",
					2));
	env_array = env_to_str(mini->envvars);
	if (!env_array)
	{
		perror("Environment conversion failed");
		return ;
	}
	execve(nodes[0], nodes, env_array);
	free_tab(env_array);
}

void	exec_cmd_with_path(char *path, char **nodes, t_mini *mini)
{
	char	**env_array;

	env_array = env_to_str(mini->envvars);
	if (!env_array)
	{
		perror("Environment conversion failed");
		return ;
	}
	execve(path, nodes, env_array);
	free_tab(env_array);
}

char	*check_path(char *bin, char *command)
{
	DIR				*folder;
	struct dirent	*item;
	char			*path;

	path = NULL;
	folder = opendir(bin);
	if (!folder)
		return (NULL);
	item = readdir(folder);
	while (item)
	{
		if (ft_strncmp(item->d_name, command, ft_strlen(command) + 1) == 0)
		{
			path = path_join(bin, item->d_name);
			break ;
		}
		item = readdir(folder);
	}
	closedir(folder);
	return (path);
}

char	*path_join(const char *s1, const char *s2)
{
	char	*tmp;
	char	*path;

	tmp = ft_strjoin(s1, "/");
	path = ft_strjoin(tmp, s2);
	free(tmp);
	return (path);
}
