/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executing.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bfiquet <bfiquet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 09:48:49 by bfiquet           #+#    #+#             */
/*   Updated: 2025/05/27 16:29:00 by tchampio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTING_H
# define EXECUTING_H

# include "../libft/includes/libft.h"
# include "parser.h"
# include "prompt.h"
# include "env.h"
# include <stdio.h>
# include <signal.h>
# include <fcntl.h>
# include <dirent.h>

typedef enum e_redir_type
{
	REDIR_IN,
	REDIR_OUT,
	_REDIR_APPEND,
	_REDIR_HEREDOC,
	NOREDIR
}	t_redir_type;

typedef struct s_redir
{
	t_redir_type	type;
	char			*filename;
	char			*delim;
	int				fd;
	struct s_redir	*next;
}	t_redir;

typedef struct s_cmd
{
	char			**cmd;
	pid_t			pid;
	t_redir			*redirs;
	struct s_cmd	*next;
	struct s_cmd	*prev;
	int				pipe_fd[2];
}	t_cmd;

typedef struct s_mini
{
	pid_t				pid;
	int					last;
	int					fdin;
	int					fdout;
	int					last_ret;
	char				*command;
	t_node				*head;
	t_envvars			*envvars;
	t_parser			parser;
	t_prompt			prompt;
	int					fd_history;
	bool				has_command_typed;
	bool				is_in_fork;
}	t_mini;

void			exec_cmd_without_path(t_mini *mini, char **nodes);
void			exec_cmd_with_path(char *path, char **nodes, t_mini *mini);
int				exec(t_mini *mini, char **nodes);
char			*check_path(char *bin, char *command);
void			redir_and_exec(t_mini *mini, t_node *nodes);
int				exec_cmd(t_mini *mini, char **nodes);
void			free_tab(char **tab);
char			*path_join(const char *s1, const char *s2);
int				is_builtin(char *cmd);
int				exec_builtin(char **cmd, t_mini *mini, t_cmd *_cmd);
int				ft_pwd(void);
void			ft_close(int fd);
int				ft_env(t_envvars *env);
int				ft_echo(char **cmd, t_mini *mini);
int				ft_cd(t_mini *mini, char **cmd);
int				ft_exit(char **cmd, t_mini *mini, t_cmd *_cmd);
int				ft_export(char **cmd, t_envvars *env);
int				ft_pwd(void);
int				ft_unset(char **cmd, t_envvars *env);
void			add_cmd_back(t_cmd **list, t_cmd *newcmd);
void			add_redirect_back(t_redir **list, t_redir *newredir);
t_redir			*redirect_new(t_redir_type type, char *filename,
					char *delimiter, int fd);
t_cmd			*create_cmd(char **args);
void			add_cmd_back(t_cmd **list, t_cmd *newcmd);
int				get_redir_fd(t_redir_type redir);
bool			is_redirection(t_tokentype tokentype);
void			free_cmd(t_cmd *cmd);
void			add_arg_to_cmd(t_cmd *cmd, t_node *arg);
void			free_redirs(t_redir *redir);
t_cmd			*parse_nodes(t_mini *mini, t_node *nodes);
void			exec_commands(t_mini *mini, t_cmd *cmds);
t_redir_type	get_redir_type(t_tokentype token);
void			reset_redirs(t_mini *mini);
void			clean_pipes(t_cmd *cmd, int *prev_fd);
bool			create_pipe(t_cmd *cmd);
void			save_redirs(t_mini *mini);
t_node			*parser_parse(t_parser *parser, char *in_str, t_mini *mini);
char			*handle_envvars(char *str, t_mini *mini);
char			*f_pwd(void);
int				check_envvar(char *in_str);
int				handle_heredoc(t_mini *mini, char *delim);
char			*handle_varname(char *str, char *dup, int *i, t_mini *mini);
int				has_redir(char *str);
int				is_redir(char c);
int				is_quote(char c);
void			ft_close_fds(t_mini *mini);
void			init_values_parse_nodes(t_cmd **cmds, t_cmd **current,
					t_node **tmp, t_node *nodes);
void			close_pipes(t_cmd *cmd);
void			connect_pipes(t_mini *mini, t_cmd *cmd, t_cmd *cmd_list);
int				execute_commands(t_cmd *cmd_list, t_mini *mini);
void			save_redirections(t_mini *mini);
int				handle_in_redirections(int *fd, t_redir *redir);
int				handle_out_redirections(int *fd, t_redir *redir);
int				handle_redirections(t_cmd *cmd, t_mini *mini);
void			restore_std_fds(t_mini *mini);
void			cleanup_child_resources(t_mini *mini, t_cmd *allcmds);
void			close_all_pipes(t_cmd *cmd_list);
int				setup_pipes(t_cmd *cmd);
void			_reset_redirs_child(t_mini *mini);
void			wait_all_cmds(t_mini *mini, t_cmd *cmd_list);
int				_wifexited(int status);
int				_wtermsig(int status);
int				_wexitstatus(int status);
int				_wifsignaled(int status);

#endif
