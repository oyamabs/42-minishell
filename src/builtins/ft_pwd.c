/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bfiquet <bfiquet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 10:12:36 by bfiquet           #+#    #+#             */
/*   Updated: 2025/04/15 10:42:34 by bfiquet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/executing.h"

char	*f_pwd(void)
{
	char	*cwd;

	cwd = getcwd(NULL, 0);
	if (cwd != NULL)
		return (cwd);
	else
		return (perror("Getrcwd Error"), NULL);
	return (0);
}

int	ft_pwd(void)
{
	char	*cwd;

	cwd = f_pwd();
	if (cwd)
		printf("%s\n", cwd);
	free(cwd);
	return (0);
}
