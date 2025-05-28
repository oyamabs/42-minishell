/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envvars.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bfiquet <bfiquet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 10:03:49 by bfiquet           #+#    #+#             */
/*   Updated: 2025/05/14 13:58:29 by tchampio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/executing.h"
#include "../../includes/env.h"

static char	*append_segment(char *dup, char *str, int start, int end)
{
	char	*tmp;
	char	*seg;

	seg = ft_substr(str, start, end - start);
	if (!seg)
	{
		free(dup);
		return (NULL);
	}
	tmp = ft_strjoin(dup, seg);
	free(seg);
	free(dup);
	if (!tmp)
		return (NULL);
	return (tmp);
}

char	*handle_status(char *dup, t_envctx *ctx, t_mini *mini)
{
	char	*tmp;
	char	*new_dup;

	tmp = ft_itoa(mini->last_ret);
	if (!tmp)
		return (NULL);
	new_dup = ft_strjoin(dup, tmp);
	free(tmp);
	free(dup);
	if (!new_dup)
		return (NULL);
	dup = new_dup;
	ctx->i += 1;
	return (dup);
}

char	*handle_dollar(char *str, char *dup, t_envctx *ctx, t_mini *mini)
{
	char	*res;

	if (ctx->i > ctx->start)
	{
		dup = append_segment(dup, str, ctx->start, ctx->i);
		if (!dup)
			return (NULL);
	}
	res = handle_edge_cases(str, dup, ctx);
	if (res)
		return (free(dup), res);
	if (str[ctx->i + 1] == '?')
		dup = handle_status(dup, ctx, mini);
	else
		dup = handle_varname(str, dup, &ctx->i, mini);
	ctx->start = ctx->i + 1;
	return (dup);
}

static char	*process_env(char *str, t_mini *mini, char *dup)
{
	t_envctx	ctx;
	int			squote;
	int			dquote;

	ctx.i = 0;
	ctx.start = 0;
	squote = 0;
	dquote = 0;
	if (!str)
		return (NULL);
	while (str[ctx.i])
	{
		update_quotes(str[ctx.i], &squote, &dquote);
		if (str[ctx.i] == '$' && !squote)
		{
			dup = handle_dollar(str, dup, &ctx, mini);
			if (!dup)
				return (NULL);
		}
		if (str[ctx.i])
			ctx.i++;
	}
	if (ctx.i > ctx.start)
		dup = append_segment(dup, str, ctx.start, ctx.i);
	return (dup);
}

char	*handle_envvars(char *str, t_mini *mini)
{
	char	*dup;

	dup = ft_strdup("");
	if (!dup)
		return (NULL);
	dup = process_env(str, mini, dup);
	if (!dup)
		return (NULL);
	return (dup);
}
