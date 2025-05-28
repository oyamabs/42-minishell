/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   argutils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bfiquet <bfiquet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 17:23:58 by tchampio          #+#    #+#             */
/*   Updated: 2025/05/14 13:51:32 by bfiquet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/executing.h"

int	count_cmd_args(char **args)
{
	int		counter;

	if (!args)
		return (0);
	counter = 0;
	while (args[counter])
		counter++;
	return (counter);
}

void	add_arg_to_cmd(t_cmd *command, t_node *arg)
{
	char	**new_args;
	int		old_args_count;
	int		i;

	old_args_count = count_cmd_args(command->cmd);
	new_args = malloc(sizeof(char *) * (old_args_count + 2));
	if (!new_args)
		return ;
	i = 0;
	while (i < old_args_count)
	{
		new_args[i] = ft_strdup(command->cmd[i]);
		i++;
	}
	new_args[i] = ft_strdup(arg->content);
	new_args[++i] = NULL;
	free_tab(command->cmd);
	command->cmd = new_args;
}

void	free_cmd(t_cmd *cmd)
{
	t_cmd	*current;
	t_cmd	*next;

	if (!cmd)
		return ;
	current = cmd;
	while (current)
	{
		if (current->cmd)
			free_tab(current->cmd);
		free_redirs(current->redirs);
		next = current->next;
		free(current);
		current = next;
	}
}

int	has_redir(char *str)
{
	int	i;

	if (!str)
		return (0);
	i = 0;
	while (str[i])
	{
		if (str[i] == '|' || str[i] == '<' || str[i] == '>')
			return (1);
		i++;
	}
	return (0);
}
