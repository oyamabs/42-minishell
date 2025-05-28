/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bfiquet <bfiquet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 13:26:26 by freddy            #+#    #+#             */
/*   Updated: 2025/04/29 11:30:27 by bfiquet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENV_H
# define ENV_H

# include <stddef.h>
# include <stdbool.h>

typedef struct s_env
{
	char	key[255];
	char	value[4096];
}	t_env;

typedef struct s_envvars
{
	t_env	**vars;
	size_t	varnumber;
}	t_envvars;

typedef struct s_envctx
{
	int	i;
	int	start;
}	t_envctx;

void		print_env(t_env	*env);
void		print_envvars(t_envvars *vars);
t_env		*add_env(t_envvars *envvars, const char *exported);
t_env		*rem_env(t_envvars *vars);
t_env		*update_env(t_envvars *vars);
t_envvars	*init_envvars(char **envp);
t_env		*search_env(t_envvars *vars, const char *key);
void		remove_env(t_envvars *vars, const char *key);
bool		try_change_env(t_envvars *envvars, const char *exported);
t_env		*create_t_envvar(const char *key, const char *value, int size);
char		**env_to_str(t_envvars *envvars);
void		free_env(t_envvars *envvars);
void		update_quotes(char c, int *squote, int *dquote);
char		*split_quotes(char *str, int j);
char		*handle_edge_cases(char *str, char *dup, t_envctx *ctx);
char		*is_in_env(t_envvars *envvar, char *target);
t_env		*search_env_envvar(t_envvars *vars, const char *key);

#endif
