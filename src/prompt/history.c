/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchampio <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 17:26:54 by tchampio          #+#    #+#             */
/*   Updated: 2025/04/29 17:26:57 by tchampio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/history.h"
#include "../../libft/includes/libft.h"
#include <stdio.h>
#include <readline/history.h>
#include <stdio.h>

int	init_history(const char *filename)
{
	int	fd;

	fd = open(filename, O_APPEND | O_CREAT | O_RDWR, S_IRUSR | S_IWUSR);
	if (fd < 0)
	{
		printf("There was an error with the creation of %s\n",
			filename);
	}
	return (fd);
}

void	add_to_history(const char *filename, const char *cmd)
{
	int	bytes_written;
	int	fd;

	fd = init_history(filename);
	if (fd > 0)
	{
		bytes_written = write(fd, cmd, ft_strlen(cmd));
		bytes_written += write(fd, "\n", 1);
		close(fd);
	}
	add_history(cmd);
}
