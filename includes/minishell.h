/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: freddy </var/spool/mail/freddy>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 18:00:33 by freddy            #+#    #+#             */
/*   Updated: 2025/04/21 14:31:37 by freddy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# define HISTORY_FILENAME ".minishell_history"
# include <stdio.h>
# include "prompt.h"
# include "env.h"
# include "parser.h"
# include "history.h"
# include "executing.h"

extern int	g_signal;

#endif
