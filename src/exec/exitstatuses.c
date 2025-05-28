/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exitstatuses.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchampio <tchampio@student.42lehavre.      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 16:21:04 by tchampio          #+#    #+#             */
/*   Updated: 2025/05/27 16:32:08 by tchampio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/executing.h"

// Everything is pulled from /usr/include/bits/waitstatus.h
// to avoid using the macros (as I am not quite sure it's allowed)
int	_wtermsig(int status)
{
	return (status & 0x7f);
}

int	_wifexited(int status)
{
	return (_wtermsig(status) == 0);
}

int	_wexitstatus(int status)
{
	return ((status & 0xff00) >> 8);
}

int	_wifsignaled(int status)
{
	return (((signed char)(((status) & 0x7f) + 1) >> 1) > 0);
}
