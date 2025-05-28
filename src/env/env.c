/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bfiquet <bfiquet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 17:23:23 by tchampio          #+#    #+#             */
/*   Updated: 2025/05/22 13:10:30 by bfiquet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/env.h"
#include "../../includes/stringutils.h"
#include "../../libft/includes/libft.h"
#include "../../includes/executing.h"
#include <stdio.h>
#include <stdlib.h>

void	remove_env(t_envvars *vars, const char *key)
{
	size_t	keysize;
	size_t	i;

	if (!vars || !key)
		return ;
	keysize = ft_strlen(key);
	i = 0;
	while (i < vars->varnumber)
	{
		if (ft_strncmp(key, vars->vars[i]->key, keysize + 1) == -61
			|| (ft_strncmp(key, vars->vars[i]->key, keysize + 1) == 0
				&& ft_strchr(key, '=') == 0))
		{
			ft_strlcpy(vars->vars[i]->key, "", 1);
			break ;
		}
		i++;
	}
}

size_t	get_envp_size(char **envp)
{
	size_t	i;

	i = 0;
	while (envp[i])
		i++;
	return (i);
}

t_envvars	*init_envvars(char **envp)
{
	t_envvars	*envvars;
	char		*key;
	char		*value;
	size_t		i;

	envvars = malloc(sizeof(*envvars));
	if (envvars == NULL)
		return (NULL);
	i = get_envp_size(envp);
	envvars->vars = malloc(sizeof(t_env) * i);
	if (envvars->vars == NULL)
	{
		free(envvars);
		return (NULL);
	}
	i = 0;
	while (envp[i])
	{
		key = envp[i];
		value = ft_strchr(envp[i], '=');
		envvars->vars[i] = create_t_envvar(key, value, value - key);
		i++;
	}
	envvars->varnumber = i;
	return (envvars);
}

char	*create_env_entry(t_env *var)
{
	char	*entry;
	size_t	total_len;

	total_len = ft_strlen(var->key) + ft_strlen(var->value) + 4;
	entry = malloc(sizeof(char) * total_len);
	if (!entry)
		return (NULL);
	ft_strlcpy(entry, var->key, total_len);
	if (var->key[0] && var->key[ft_strlen(var->key) - 1]
		!= '=' && var->value[0])
		ft_strlcat(entry, "=", total_len);
	ft_strlcat(entry, var->value, total_len);
	return (entry);
}

char	**env_to_str(t_envvars *envvars)
{
	char	**env;
	size_t	i;

	env = malloc(sizeof(char *) * (envvars->varnumber + 1));
	if (!env)
		return (NULL);
	i = 0;
	while (i < envvars->varnumber)
	{
		env[i] = create_env_entry(envvars->vars[i]);
		if (!env[i])
			return (free_tab(env), NULL);
		i++;
	}
	env[i] = NULL;
	return (env);
}
