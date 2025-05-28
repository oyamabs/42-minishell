/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchampio <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 17:27:11 by tchampio          #+#    #+#             */
/*   Updated: 2025/05/19 15:12:19 by tchampio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/signals.h"
#include "../../libft/includes/libft.h"
#include <signal.h>
#include <readline/readline.h>
#include <unistd.h>
#include <stdlib.h>

int	event(void)
{
	return (EXIT_SUCCESS);
}

void	sigint_handling(int sig)
{
	(void)sig;
	if (g_signal == 10)
	{
		rl_replace_line("", 0);
		rl_redisplay();
		rl_done = 1;
		g_signal = 1;
	}
	else
	{
		ft_printf("\n");
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
		g_signal = 2;
	}
}

void	sigquit_handling(int sig)
{
	ft_printf("Quit: %d\n", sig);
	(void)sig;
}

void	init_signals(void)
{
	rl_event_hook = event;
	signal(SIGINT, sigint_handling);
	signal(SIGQUIT, SIG_IGN);
}
