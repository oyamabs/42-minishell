/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printenv.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bfiquet <bfiquet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 17:23:31 by tchampio          #+#    #+#             */
/*   Updated: 2025/05/12 10:20:18 by bfiquet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/env.h"
#include "../../includes/executing.h"
#include <stdio.h>

void	print_env(t_env *env)
{
	printf("%s -> %s\n", env->key, env->value);
}

void	print_envvars(t_envvars *envvars)
{
	size_t	i;

	i = 0;
	while (i < envvars->varnumber)
	{
		if (envvars->vars[i]->key[0] != '\0' && envvars->vars[i]->value[0]
			&& envvars->vars[i]->key[ft_strlen(envvars->vars[i]->key)
				- 1] != '=')
			printf("%s=%s\n", envvars->vars[i]->key, envvars->vars[i]->value);
		else if (envvars->vars[i]->key[0] != '\0' && envvars->vars[i]->value[0])
			printf("%s%s\n", envvars->vars[i]->key, envvars->vars[i]->value);
		else if (envvars->vars[i]->key[0] != '\0' && envvars->vars[i]
			->key[ft_strlen(envvars->vars[i]->key) - 1] == '=')
			printf("%s\n", envvars->vars[i]->key);
		i++;
	}
}
