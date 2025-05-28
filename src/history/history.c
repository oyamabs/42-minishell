/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchampio <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 17:26:04 by tchampio          #+#    #+#             */
/*   Updated: 2025/04/29 17:26:05 by tchampio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/history.h"
#include "../../libft/includes/libft.h"
#include <stdio.h>
#include <readline/history.h>
#include <stdio.h>

void	read_history_file(const char *filename)
{
	char	*line;
	char	trimmed[99999];
	int		fd;

	ft_bzero(trimmed, 99999);
	fd = open(filename, O_RDONLY);
	if (fd < 0)
		return ((void)printf("There was an error with the creation of %s\n",
				filename));
	line = get_next_line(fd);
	while (line)
	{
		ft_strlcpy(trimmed, line, ft_strlen(line));
		add_history(trimmed);
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
}

int	init_history(const char *filename)
{
	int	fd;

	fd = open(filename, O_APPEND | O_CREAT | O_RDWR, S_IRUSR | S_IWUSR);
	if (fd < 0)
	{
		printf("There was an error with the creation of %s\n",
			filename);
	}
	read_history_file(filename);
	return (fd);
}

void	add_to_history(const char *filename, const char *cmd)
{
	int	bytes_written;
	int	fd;

	if (!cmd || cmd[0] == '\0' || cmd[0] == '\n')
		return ;
	fd = init_history(filename);
	if (fd > 0)
	{
		bytes_written = write(fd, cmd, ft_strlen(cmd));
		bytes_written += write(fd, "\n", 1);
		close(fd);
	}
	add_history(cmd);
}
