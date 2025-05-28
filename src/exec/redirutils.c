/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirutils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchampio <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 17:25:22 by tchampio          #+#    #+#             */
/*   Updated: 2025/05/16 12:51:23 by tchampio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/executing.h"

bool	is_redirection(t_tokentype type)
{
	if (type == REDIR_APPEND || type == REDIR_HEREDOC
		|| type == REDIR_OUTFILE || type == REDIR_INFILE)
		return (true);
	return (false);
}

t_redir_type	get_redir_type(t_tokentype token)
{
	if (token == REDIR_APPEND)
		return (_REDIR_APPEND);
	if (token == REDIR_HEREDOC)
		return (_REDIR_HEREDOC);
	if (token == REDIR_OUTFILE)
		return (REDIR_OUT);
	if (token == REDIR_INFILE)
		return (REDIR_IN);
	return (NOREDIR);
}

int	get_redir_fd(t_redir_type redir)
{
	if (redir == REDIR_OUT || redir == _REDIR_APPEND)
		return (STDOUT_FILENO);
	else if (redir == REDIR_IN || redir == _REDIR_HEREDOC)
		return (STDIN_FILENO);
	return (-1);
}

void	free_redirs(t_redir *redir)
{
	t_redir	*current;
	t_redir	*next;

	if (!redir)
		return ;
	current = redir;
	while (current)
	{
		if (current->filename)
			free(current->filename);
		if (current->delim)
			free(current->delim);
		next = current->next;
		free(current);
		current = next;
	}
}

void	ft_close_fds(t_mini *mini)
{
	close(mini->fdin);
	close(mini->fdout);
	mini->fdin = -1;
	mini->fdout = -1;
}
