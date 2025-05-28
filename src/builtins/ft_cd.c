/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bfiquet <bfiquet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 10:12:29 by bfiquet           #+#    #+#             */
/*   Updated: 2025/05/12 12:15:59 by bfiquet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/executing.h"

char	*is_in_env(t_envvars *envvar, char *target)
{
	size_t	i;

	i = 0;
	while (i < envvar->varnumber)
	{
		if (ft_strcmp(envvar->vars[i]->key, target) == 0)
			return (envvar->vars[i]->value);
		i++;
	}
	return (NULL);
}

bool	check_cd_allowing(t_mini *mini, char **cmd, char **target)
{
	if (!cmd[1])
	{
		*target = is_in_env(mini->envvars, "HOME");
		if (!*target)
			return (ft_putstr_fd("minishell: cd: HOME not set\n", 2), false);
	}
	else if (cmd[2])
		return (ft_putstr_fd("minishell: cd: too many arguments\n", 2), false);
	else
		*target = cmd[1];
	return (true);
}

int	ft_cd(t_mini *mini, char **cmd)
{
	char	*target;
	char	*oldpwd;
	char	*str;
	char	*newpwd;

	if (!check_cd_allowing(mini, cmd, &target))
		return (1);
	oldpwd = f_pwd();
	if (chdir(target) == -1)
		return (free(oldpwd), perror("minishell: cd"), 1);
	if (oldpwd)
		return (str = ft_strjoin("OLDPWD=", oldpwd),
			try_change_env(mini->envvars, str), free(str), str = f_pwd(),
			newpwd = ft_strjoin("PWD=", str),
			try_change_env(mini->envvars, newpwd), free(oldpwd),
			free(str), free(newpwd), 0);
	else
		return (str = f_pwd(), newpwd = ft_strjoin("PWD=", str),
			try_change_env(mini->envvars, newpwd), free(oldpwd),
			free(str), free(newpwd), 0);
}
