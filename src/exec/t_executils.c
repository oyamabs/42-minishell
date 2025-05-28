/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_executils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchampio <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 17:25:34 by tchampio          #+#    #+#             */
/*   Updated: 2025/04/29 17:25:36 by tchampio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/executing.h"
#include "../../libft/includes/libft.h"

t_cmd	*create_cmd(char **args)
{
	t_cmd	*cmd;

	cmd = ft_calloc(sizeof(t_cmd), 1);
	if (!cmd)
		return (NULL);
	cmd->cmd = args;
	cmd->prev = NULL;
	cmd->next = NULL;
	cmd->pipe_fd[0] = -1;
	cmd->pipe_fd[1] = -1;
	return (cmd);
}

t_redir	*redirect_new(t_redir_type type, char *filename,
			char *delimiter, int fd)
{
	t_redir	*redir;

	redir = malloc(sizeof(t_redir));
	if (!redir)
		return (NULL);
	redir->type = type;
	if (filename)
		redir->filename = ft_strdup(filename);
	else
		redir->filename = NULL;
	if (delimiter)
		redir->delim = ft_strdup(delimiter);
	else
		redir->delim = NULL;
	redir->fd = fd;
	redir->next = NULL;
	return (redir);
}

void	add_redirect_back(t_redir **list, t_redir *newredir)
{
	t_redir	*tmp;

	if (!list || !newredir)
		return ;
	if (!*list)
	{
		*list = newredir;
		return ;
	}
	tmp = *list;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = newredir;
}

void	add_cmd_back(t_cmd **list, t_cmd *newcmd)
{
	t_cmd	*tmp;

	if (!list || !newcmd)
		return ;
	if (!*list)
	{
		*list = newcmd;
		return ;
	}
	tmp = *list;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = newcmd;
	newcmd->prev = tmp;
}
