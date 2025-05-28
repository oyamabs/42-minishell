/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: freddy </var/spool/mail/freddy>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 14:20:36 by freddy            #+#    #+#             */
/*   Updated: 2025/04/28 13:35:01 by freddy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PROMPT_H
# define PROMPT_H

# include "env.h"
# include <stdbool.h>
# define RELATIVE_PATH_SIZE 1024
# define ABSOLUTE_PATH_SIZE 2048

typedef struct s_prompt
{
	char	rwd[RELATIVE_PATH_SIZE]; // current working directory
	char	cwd[ABSOLUTE_PATH_SIZE]; // Working directory (relative to home)
	bool	is_root; // should be false
	char	username[ABSOLUTE_PATH_SIZE];
	char	prompt[ABSOLUTE_PATH_SIZE];
}	t_prompt;

void	get_relative_path(t_envvars *envvars, t_prompt *prompt);
bool	is_root(t_envvars *envvars);
void	create_prompt(t_envvars *envvars, t_prompt *prompt);

#endif
