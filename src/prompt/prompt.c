/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchampio <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 17:27:03 by tchampio          #+#    #+#             */
/*   Updated: 2025/04/29 17:27:04 by tchampio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/prompt.h"
#include "../../includes/env.h"
#include <stdio.h>
#include <stdlib.h>
#include "../../libft/includes/libft.h"

// The path returned and displayed depends if $USER is in his $HOME or not.
// if $USER is in his $HOME we display ~/path/of/cwd
// if not we display /path/of/cwd
void	get_relative_path(t_envvars *envvars, t_prompt *prompt)
{
	t_env	*home;
	bool	home_allocated;
	int		i;

	ft_bzero(prompt->rwd, 1024);
	home_allocated = false;
	if (!getcwd(prompt->cwd, 1024))
		return ;
	home = search_env(envvars, "HOME");
	if (!home)
	{
		home = create_t_envvar("", "thispathshouldnotexistswtf", 0);
		home_allocated = true;
	}
	if (ft_strncmp(home->value, prompt->cwd, ft_strlen(home->value)))
		ft_memcpy(prompt->rwd, prompt->cwd, ft_strlen(prompt->cwd));
	else
	{
		i = ft_strlen(home->value);
		prompt->rwd[0] = '~';
		ft_memcpy(prompt->rwd + 1, prompt->cwd + i, ft_strlen(prompt->cwd) - i);
	}
	if (home_allocated)
		free(home);
}

bool	is_root(t_envvars *envvars)
{
	t_env	*user;

	user = search_env(envvars, "USER");
	if (!user)
		return (false);
	if (ft_strncmp(user->value, "root", ft_strlen("root")))
		return (false);
	else
		return (true);
}

// static void	reset_prompt(t_prompt *prompt)
// {
// 	size_t	i;

// 	i = 0;
// 	while (i < ft_strlen(prompt->prompt))
// 		prompt->prompt[i++] = 0;
// }

void	create_prompt(t_envvars *envvars, t_prompt *prompt)
{
	t_env	*user;

	user = search_env(envvars, "USER");
	ft_bzero(prompt->prompt, 2048);
	get_relative_path(envvars, prompt);
	ft_strlcat(prompt->prompt, "\e[0;34m", 2048);
	ft_strlcat(prompt->prompt, prompt->rwd, 2048);
	ft_strlcat(prompt->prompt, "\e[0m \e[1;36m", 2048);
	if (user)
	{
		ft_strlcat(prompt->prompt, user->value, 2048);
		ft_strlcat(prompt->prompt, " ", 2048);
	}
	ft_strlcat(prompt->prompt, "\e[0m", 2048);
	if (is_root(envvars))
		ft_strlcat(prompt->prompt, "# ", 2048);
	else
		ft_strlcat(prompt->prompt, "$ ", 2048);
}
