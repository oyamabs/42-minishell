/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   addenv.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bfiquet <bfiquet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 17:23:11 by tchampio          #+#    #+#             */
/*   Updated: 2025/05/12 12:57:15 by bfiquet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/env.h"
#include "../../includes/stringutils.h"
#include <stdio.h>
#include <stdlib.h>
#include "../../libft/includes/libft.h"

t_env	*create_t_envvar(const char *key, const char *value, int size)
{
	t_env	*env;

	env = malloc(sizeof(*env));
	if (!env)
		return (NULL);
	ft_strlcpy(env->key, key, size + 1);
	if (value)
		ft_strlcpy(env->value, value + 1, ft_strlen(value));
	else
		env->value[0] = '\0';
	return (env);
}

bool	try_change_env(t_envvars *envvars, const char *exported)
{
	char	*key;
	char	*value;
	char	*searched;
	int		key_len;
	t_env	*found;

	key = (char *)exported;
	value = ft_strchr(key, '=');
	if (value)
		key_len = value - key;
	else
		key_len = ft_strlen(key);
	searched = ft_strndup(key, key_len);
	if (!searched)
		return (false);
	found = search_env(envvars, searched);
	if (!found)
		return (free(searched), false);
	if (value)
		ft_strlcpy(found->value, value + 1, ft_strlen(value + 1) + 1);
	else
		ft_strlcpy(found->value, "", 1);
	free(searched);
	return (true);
}

t_env	*add_env(t_envvars *envvars, const char *exported)
{
	t_env	*newenv;
	char	*key;
	char	*value;
	int		i;
	char	*real_key;

	i = 0;
	if (!envvars || !exported)
		return (NULL);
	key = (char *)exported;
	value = ft_strchr(exported, '=');
	if (!value)
		return (NULL);
	while (exported[i] && exported[i] != '=')
		i++;
	real_key = ft_substr(key, 0, i);
	if (is_in_env(envvars, real_key) && !value)
		return (free(real_key), NULL);
	if (try_change_env(envvars, exported))
		return (free(real_key), NULL);
	newenv = create_t_envvar(key, value, value - key + 1);
	if (!newenv)
		return (free(real_key), NULL);
	envvars->vars[envvars->varnumber] = newenv;
	return (envvars->varnumber++, free(real_key), newenv);
}

t_env	*search_env(t_envvars *vars, const char *key)
{
	size_t	keysize;
	size_t	i;
	t_env	*found;

	if (!vars || !key)
		return (NULL);
	keysize = ft_strlen(key);
	i = 0;
	found = NULL;
	while (i < vars->varnumber && !found)
	{
		if (ft_strncmp(key, vars->vars[i]->key, keysize + 1) == 0
			|| ft_strncmp(key, vars->vars[i]->key, keysize + 1) == -61
			|| ft_strncmp(key, vars->vars[i]->key, keysize + 1) == 61)
			found = vars->vars[i];
		i++;
	}
	return (found);
}

void	free_env(t_envvars *envvars)
{
	size_t	i;

	i = 0;
	while (i < envvars->varnumber)
	{
		free(envvars->vars[i]);
		i++;
	}
	free(envvars->vars);
}
