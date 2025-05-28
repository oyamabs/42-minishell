/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bfiquet <bfiquet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 10:12:49 by bfiquet           #+#    #+#             */
/*   Updated: 2025/04/29 17:18:47 by tchampio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/executing.h"
#include "../../includes/env.h"

static int	check_n_flags(char **cmd, int *option)
{
	int	i;
	int	j;

	i = 1;
	while (cmd[i])
	{
		if (cmd[i][0] != '-')
			break ;
		j = 1;
		while (cmd[i][j] == 'n')
			j++;
		if (cmd[i][j] != '\0')
			break ;
		*option = 1;
		i++;
	}
	return (i);
}

char	*split_quotes(char *str, int j)
{
	char	*res;
	int		i;
	char	quote;

	i = 0;
	res = malloc(ft_strlen(str) + 1);
	if (!res)
		return (NULL);
	while (str[i])
	{
		if (str[i] == '\'' || str[i] == '"')
		{
			quote = str[i];
			i++;
			while (str[i] && str[i] != quote)
				res[j++] = str[i++];
			if (str[i] == quote)
				i++;
		}
		else
			res[j++] = str[i++];
	}
	res[j] = '\0';
	return (res);
}

int	ft_echo(char **cmd, t_mini *mini)
{
	int		option;
	int		i;

	option = 0;
	i = 1;
	if (cmd[1] && ft_strncmp(cmd[1], "-n", 2) == 0)
		i = check_n_flags(cmd, &option);
	while (cmd[i])
	{
		if (cmd[i + 1])
			printf("%s ", cmd[i]);
		else
			printf("%s", cmd[i]);
		i++;
	}
	if (option == 0)
		printf("\n");
	mini->last_ret = 0;
	return (mini->last_ret);
}

void	update_quotes(char c, int *squote, int *dquote)
{
	if (c == '"' && !(*squote))
		*dquote = !(*dquote);
	else if (c == '\'' && !(*dquote))
		*squote = !(*squote);
}
