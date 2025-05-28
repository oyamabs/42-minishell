/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bfiquet <bfiquet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 10:12:41 by bfiquet           #+#    #+#             */
/*   Updated: 2025/05/26 14:04:40 by tchampio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/executing.h"
#include "../../includes/env.h"
#include <unistd.h>

int	ft_strisnum(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}

static void	print_exit_error(char *arg)
{
	ft_putstr_fd("minishell: exit: ", STDERR_FILENO);
	ft_putstr_fd(arg, STDERR_FILENO);
	ft_putendl_fd(": numeric argument required", STDERR_FILENO);
}

static void	clean_exit(t_mini *mini, char **cmd, int exit_code, t_cmd *_cmd)
{
	free_env(mini->envvars);
	free(mini->envvars);
	(void)cmd;
	delete_xbuffer(mini->parser.tokenizer.buffer);
	clear_list(&mini->head);
	free_cmd(_cmd);
	exit(exit_code);
}

int	ft_exit(char **cmd, t_mini *mini, t_cmd *_cmd)
{
	int	exit_code;

	if (mini->is_in_fork)
		return (0);
	ft_putstr_fd("exit\n", STDERR_FILENO);
	ft_close_fds(mini);
	if (cmd[1] && !ft_strisnum(cmd[1]))
	{
		print_exit_error(cmd[1]);
		clean_exit(mini, cmd, 2, _cmd);
	}
	if (cmd[1] && cmd[2])
	{
		ft_putendl_fd("minishell: exit: too many arguments", STDERR_FILENO);
		return (1);
	}
	if (!cmd[1])
		clean_exit(mini, cmd, mini->last_ret, _cmd);
	exit_code = ft_atoi(cmd[1]);
	clean_exit(mini, cmd, exit_code, _cmd);
	return (0);
}
