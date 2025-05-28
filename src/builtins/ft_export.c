/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bfiquet <bfiquet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 10:12:43 by bfiquet           #+#    #+#             */
/*   Updated: 2025/05/09 09:54:40 by bfiquet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/executing.h"

int	is_valid_arg(char *value)
{
	int	i;
	int	equal_found;

	i = 0;
	equal_found = 0;
	if (!value || value[0] == '=')
		return (-3);
	if (ft_isdigit(value[0]))
		return (0);
	while (value[i])
	{
		if (value[i] == '=')
			equal_found = 1;
		if (!equal_found && (!ft_isalnum(value[i]) && value[i] != '_'))
			return (-1);
		else
		{
			if (value[i] == '(' || value[i] == ')'
				|| value[i] == '!' || value[i] == ';')
				return (-1);
		}
		i++;
	}
	return (1);
}

static int	print_error(int error, char *arg)
{
	int		i;

	if (error == 0 || error == -3 || error == -1)
	{
		ft_putstr_fd(" minishell: export: `", STDERR_FILENO);
		ft_putstr_fd(arg, STDERR_FILENO);
		ft_putstr_fd("': not a valid identifier ", STDERR_FILENO);
		write(STDERR_FILENO, "\n", 1);
		return (0);
	}
	i = 0;
	while (arg[i] || error == -3)
	{
		write(STDERR_FILENO, &arg[i], 1);
		i++;
	}
	write(STDERR_FILENO, "\n", 1);
	return (0);
}

void	print_sort_str(char **str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		ft_printf("%s\n", str[i]);
		i++;
	}
	free_tab(str);
}

void	sort_str(char **str)
{
	int		i;
	int		swapped;
	char	*tmp;

	if (!str || !str[0] || !str[1])
		return ;
	swapped = 1;
	while (swapped)
	{
		swapped = 0;
		i = 1;
		while (str[i])
		{
			if (ft_strcmp(str[i - 1], str[i]) > 0)
			{
				tmp = str[i - 1];
				str[i - 1] = str[i];
				str[i] = tmp;
				swapped = 1;
			}
			i++;
		}
	}
}

int	ft_export(char **cmd, t_envvars *env)
{
	int		error_code;
	int		i;

	i = 1;
	while (cmd[i])
	{
		error_code = is_valid_arg(cmd[i]);
		if (error_code != 1)
			return (print_error(error_code, cmd[i]), 1);
		else if (!cmd[i][0] || cmd[i][0] == '=')
			return (print_error(-3, cmd[i]), 1);
		else
			add_env(env, cmd[i]);
		i++;
	}
	return (0);
}
