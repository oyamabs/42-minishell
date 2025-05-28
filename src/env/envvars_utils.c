/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envvars_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bfiquet <bfiquet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 15:07:44 by bfiquet           #+#    #+#             */
/*   Updated: 2025/05/14 13:53:51 by bfiquet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/executing.h"
#include "../../includes/env.h"

char	*handle_edge_cases(char *str, char *dup, t_envctx *ctx)
{
	char	tmp[3];
	char	*joined;

	if (!str[ctx->i + 1])
	{
		dup = ft_strjoin(dup, "$");
		if (!dup)
			return (NULL);
		ctx->start = ctx->i + 1;
		return (dup);
	}
	else if (!ft_isalnum(str[ctx->i + 1])
		&& str[ctx->i + 1] != '_' && str[ctx->i + 1] != '?')
	{
		tmp[0] = '$';
		tmp[1] = str[ctx->i + 1];
		tmp[2] = '\0';
		joined = ft_strjoin(dup, tmp);
		if (!joined)
			return (NULL);
		ctx->start = ctx->i + 2;
		ctx->i += 2;
		return (joined);
	}
	return (NULL);
}

char	*quotes_redir(char *str, char *tmp, char *result)
{
	tmp = ft_strjoin(result, "'");
	result = ft_strjoin(tmp, str);
	free(tmp);
	tmp = ft_strjoin(result, "'");
	return (free(result), tmp);
}

char	*quote_redirections(char *value)
{
	int		i;
	char	*result;
	char	*tmp;
	char	str[2];

	i = 0;
	if (!value)
		return (NULL);
	result = ft_strdup("");
	if (!result)
		return (NULL);
	while (value[i])
	{
		str[0] = value[i];
		str[1] = '\0';
		if (value[i] == '|' || value[i] == '<' || value[i] == '>')
			tmp = quotes_redir(str, tmp, result);
		else
			tmp = ft_strjoin(result, str);
		free(result);
		result = tmp;
		i++;
	}
	return (result);
}

char	*handle_redir(char *dup, char *env_value)
{
	char	*tmp;
	char	*tmp2;

	if (has_redir(env_value))
	{
		tmp2 = quote_redirections(env_value);
		tmp = ft_strjoin(dup, tmp2);
		free(tmp2);
	}
	else
		tmp = ft_strjoin(dup, env_value);
	if (!tmp)
	{
		free(dup);
		return (NULL);
	}
	free(dup);
	return (tmp);
}

char	*handle_varname(char *str, char *dup, int *i, t_mini *mini)
{
	int		j;
	t_env	*env;
	char	*var_name;

	j = *i + 1;
	while (str[j] && (ft_isalnum(str[j]) || str[j] == '_'))
		j++;
	var_name = ft_substr(str, *i + 1, j - (*i + 1));
	if (!var_name)
		return (NULL);
	env = search_env(mini->envvars, var_name);
	free(var_name);
	if (env)
	{
		dup = handle_redir(dup, env->value);
		if (!dup)
			return (NULL);
	}
	*i = j - 1;
	return (dup);
}
