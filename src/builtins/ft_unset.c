/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bfiquet <bfiquet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 10:12:33 by bfiquet           #+#    #+#             */
/*   Updated: 2025/04/25 13:01:51 by bfiquet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/executing.h"
#include "../../includes/env.h"

int	ft_unset(char **cmd, t_envvars *envvars)
{
	int	i;

	i = 1;
	if (!cmd[i])
		return (-1);
	while (cmd[i])
	{
		remove_env(envvars, cmd[i]);
		i++;
	}
	return (0);
}
