/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsenodes.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchampio <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 17:24:38 by tchampio          #+#    #+#             */
/*   Updated: 2025/05/14 14:42:24 by tchampio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/executing.h"

void	add_redirection(t_mini *mini, t_node *tmp, t_cmd *current, char *target)
{
	t_redir_type	redirtype;
	t_redir			*redir;
	static int		heredoc_id = 0;
	char			hd_filename[26];
	char			*itoad_id;

	redirtype = get_redir_type(tmp->type);
	itoad_id = NULL;
	ft_bzero(hd_filename, 26);
	if (redirtype == _REDIR_HEREDOC)
	{
		itoad_id = ft_itoa(heredoc_id);
		ft_strlcat(hd_filename, "/tmp/minishell_heredoc",
			ft_strlen("/tmp/minishell_heredocxxx") + 1);
		ft_strlcat(hd_filename, itoad_id,
			ft_strlen("/tmp/minishell_heredocxxx") + 1);
		redir = redirect_new(redirtype, hd_filename, target,
				handle_heredoc(mini, target));
		heredoc_id++;
		free(itoad_id);
	}
	else
		redir = redirect_new(redirtype, target, NULL, get_redir_fd(redirtype));
	add_redirect_back(&current->redirs, redir);
}

bool	get_target_and_check_errs(t_node *tmp, char **target, t_cmd *cmds)
{
	if (tmp->next)
		*target = tmp->next->content;
	else
		*target = NULL;
	if (!*target)
		return (
			ft_putstr_fd(
				"Ça marche pas (no target or delimiter) 🫵😹\n", 2),
			free_cmd(cmds), false);
	if (tmp->next->type == PIPE || is_redirection(tmp->next->type))
		return (
			ft_putstr_fd(
				"Ça marche pas (No command after redirection) 🫵😹\n", 2),
			free_cmd(cmds), false);
	return (true);
}

bool	create_redirections_and_args(t_node **tmp, char **target,
						t_cmd *cmds[2], t_mini *mini)
{
	if (is_redirection((*tmp)->type))
	{
		if (!get_target_and_check_errs(*tmp, target, cmds[0]))
			return (false);
		add_redirection(mini, *tmp, cmds[1], *target);
		*tmp = (*tmp)->next->next;
	}
	else if ((*tmp)->type == TERM_WORD
		|| (*tmp)->type == FINISHED_DOUBLE_QUOTE
		|| (*tmp)->type == FINISHED_SINGLE_QUOTE)
	{
		add_arg_to_cmd(cmds[1], *tmp);
		(*tmp) = (*tmp)->next;
	}
	return (true);
}

bool	check_pipes(t_node **tmp, t_cmd *cmds)
{
	if ((*tmp)->type == '|' && (*tmp)->next
		&& (*tmp)->next->type == '|')
		return (
			ft_putstr_fd("Ça marche pas (empty pipe) 🫵😹\n", 2),
			free_cmd(cmds), false);
	if ((*tmp)->type == '|')
		*tmp = (*tmp)->next;
	if (!*tmp)
		return (
			ft_putstr_fd("Ça marche pas (end pipe) 🫵😹\n", 2),
			free_cmd(cmds), false);
	return (true);
}

t_cmd	*parse_nodes(t_mini *mini, t_node *nodes)
{
	t_cmd			*cmds;
	t_cmd			*current;
	t_node			*tmp;
	char			*target;
	t_cmd			*cmd_tab[2];

	init_values_parse_nodes(&cmds, &current, &tmp, nodes);
	if (tmp->type == '|')
		return (ft_putstr_fd(
				"Ça marche pas (Starting with a pipe) 🫵😹\n", 2), NULL);
	while (tmp)
	{
		if (!current || tmp->type == '|')
		{
			if (!check_pipes(&tmp, cmds))
				return (NULL);
			current = create_cmd(NULL);
			add_cmd_back(&cmds, current);
		}
		cmd_tab[0] = cmds;
		cmd_tab[1] = current;
		if (!create_redirections_and_args(&tmp, &target, cmd_tab, mini))
			return (NULL);
	}
	return (cmds);
}
