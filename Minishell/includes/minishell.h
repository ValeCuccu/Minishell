/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anpastac <anpastac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/07 12:30:56 by vacuccu           #+#    #+#             */
/*   Updated: 2026/01/22 19:57:05 by anpastac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

/* ==== DEPENDENCIES ======================================================= */
# include "../src/libft/libft.h"
# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <errno.h>
# include <string.h>
# include <signal.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <termios.h>

/* ==== ENUMS ============================================================== */
typedef enum e_redir_type
{
	REDIR_IN,
	REDIR_OUT,
	REDIR_APPEND,
	REDIR_HEREDOC
}	t_redir_type;

/* lexer token types */
typedef enum e_toktype
{
	T_WORD,
	T_PIPE,
	T_REDIR_IN,
	T_REDIR_OUT,
	T_APPEND,
	T_HEREDOC
}	t_toktype;

/* ==== NODES ============================================================== */
typedef struct s_redir
{
	t_redir_type		type;
	char				*filename;
	int					expand;
	struct s_redir		*next;
}	t_redir;

typedef struct s_cmd
{
	char				**av;
	int					is_builtin;
	t_redir				*redirs;
	struct s_cmd		*next;
}	t_cmd;

typedef struct s_env
{
	char				*key;
	char				*val;
	struct s_env		*next;
}	t_env;

typedef struct s_token
{
	t_toktype			type;
	char				*input;
	int					was_quoted;
	struct s_token		*next;
}	t_token;

typedef struct s_ms_state
{
	t_env	*env;
	t_cmd	*head;
	int		hd_idx;
}	t_ms_state;

typedef struct s_pipe_ctx
{
	int		i;
	int		n;
	t_cmd	*c;
	t_cmd	*head;
	t_env	**penv;
	pid_t	*pid_arr;
	int		prev[2];
	int		curr[2];
}	t_pipe_ctx;

typedef struct s_hd_ctx
{
	const char	*delim;
	int			expand;
	int			fd;
	char		*path;
	t_ms_state	*st;
}	t_hd_ctx;

int			get_last_status(void);
void		vc_set_last_status(int value);
void		set_last_status(t_env **penv, int code);

t_cmd		*new_cmd(char **av);
void		cmd_append(t_cmd **cmd_list, t_cmd *new_node);
void		cmd_free(t_cmd *cmd_node);
void		cmd_clear(t_cmd **cmd_list);
void		free_cmd_list(t_cmd *cmds);

t_token		*token_new(t_toktype type, const char *text);
int			token_append(t_token **head, t_token *node);
void		token_clear(t_token **head);
void		free_token_list(t_token *lst);
const char	*tok_type_name(t_toktype t);

t_redir		*redir_new(t_redir_type type, const char *filename, int expand);
void		redir_append(t_redir **redir_list, t_redir *new_node);
void		redir_free(t_redir *redir_node);
void		redir_clear(t_redir **redir_list);

void		skip_spaces(const char *s, int *i);
int			read_word(const char *s, int *i, char **out);
int			next_token(const char *s, int *i, t_token **out);
int			push_token(t_token **head, t_token *node);
t_token		*lex_line(const char *s);
t_token		*lexer_build_tokens(const char *input);

int			is_space(char c);
int			is_quote(char c);
int			is_double_quote(char c);
int			is_pipe(char c);
int			is_redir(char c);

int			append_or_heredoc(const char *s, int *i, t_toktype *type);
int			read_pipe(const char *s, int *i, t_toktype *type);
int			read_single_redir(const char *s, int *i, t_toktype *type);
int			read_operator(const char *s, int *i, t_toktype *type);

int			read_word_part(const char *s, int *i, char **acc);
int			read_single_quoted_part(const char *s, int *i, char **acc);
int			read_double_quoted_part(const char *s, int *i, char **acc);
int			read_bare_part(const char *s, int *i, char **acc);

char		*substr_dup(const char *src, int start, int end);
char		*join_and_free(char *s1, char *s2);
int			append_segment(char **dest, const char *src, int start, int end);
int			ft_strcmp(char *s1, char *s2);

int			is_var_start(char c);
int			is_var_char(char c);
int			get_var_end(const char *s, int pos);
char		*env_lookup(t_env *env, const char *name, int len);
int			expand_dollar_out(const char *src, int *i, char **res, t_env *env);
int			expand_dq_dollar(const char *src, int *cur, char **res, t_env *env);
int			handle_single_quotes(const char *src, int *i, char **res);
int			handle_double_quotes(const char *src,
				int *i, char **res, t_env *env);
int			handle_plain_text(const char *src, int *i, char **res, t_env *env);
char		*expand_out(const char *src, t_env *env);
char		*dequote_all(const char *s);
int			expand_tokens(t_token **plist, t_env *env);
char		*expand_quotes(const char *src, t_env *env);
int			dq_expand_at(const char *src, int *cur, char **res, t_env *env);
int			dq_finish(const char *src, int *i, int cur, char **res);
int			map_tok_to_redir(t_toktype op, t_redir_type *out);
int			update_state(int state, char c);
char		*dequote_all(const char *s);
int			append_char(char **out, char c);
void		remove_token(t_token **plist, t_token *prev);

int			is_builtin(char *s);
int			count_words_until_pipe(const t_token *t);
int			attach_redir(t_cmd *cmd, t_toktype op, const t_token *word_tok);
int			check_syntax_errors(t_token *t, int *exit_status);
t_cmd		*build_cmd_list(t_token *lst);
int			fill_argv_for_cmd(t_cmd *cmd, t_token **it);
void		set_builtin_flag(t_cmd *cmd);

t_cmd		*parse_input(const char *line, t_env *env, int *exit_status);

void		free_env(t_env *env);
t_env		*env_find_key(t_env *env, const char *key);
char		*get_env_value(t_env *env, const char *name);
int			env_size(t_env *env);
int			same_key(const char *a, const char *b);
int			env_update_value(t_env *node, const char *val);
int			env_add_new(t_env **env, const char *key, const char *val);

t_env		*env_new(char *key, char *val);
void		env_add_back(t_env **lst, t_env *new_node);
t_env		*build_env(char **envp);
int			env_set(t_env **env, const char *key, const char *val);
int			env_unset(t_env **env, char *key);

void		setup_signals_interactive(void);
void		setup_signals_heredoc(void);
void		ms_disable_echoctl(void);

int			bi_cd(char **av, t_env **penv);
int			bi_echo(char **av);
int			bi_env(t_env *env);
int			bi_exit_parent(char **av, t_env **penv);
int			bi_exit_child(char **av, t_env **penv);
int			bi_export(char **av, t_env **penv);
int			bi_pwd(void);
int			bi_unset(char **av, t_env **penv);

int			bi_is_builtin(const char *name);
int			bi_run_child(char **av, t_env **penv);
int			bi_run_parent(char **av, t_env **penv);

void		free_envp_array(char **envp);
t_env		*env_new_node(const char *key, const char *val);
int			split_env_entry(const char *entry, char **out_key, char **out_val);
t_env		*init_env(char **envp);
void		free_env_list(t_env *env);
char		*env_get_value(t_env *env, const char *key);
int			env_set_value(t_env **env, const char *key, const char *val);
int			env_unset_key(t_env **env, const char *key);
char		**env_to_envp_array(t_env *env);

int			ap_apply_redirs(t_redir *rlist);
int			save_stdio(int sv[2]);
int			restore_stdio(int sv[2]);
int			ms_mod256_str(const char *s);
int			ms_parse_exit_mod256(const char *s, int *ok);
int			ms_try_parse_exit(const char *s, int *out);
void		ms_close_extra_fds(void);

int			ap_run_single(t_cmd *line, t_env **penv);
int			ap_run_pipeline(t_cmd *line, t_env **penv, int n);

int			ap_run_child_exec(t_cmd *c, t_env **penv);

int			exec_external(char **argv, char **envp, t_env *env_list);
char		*resolve_cmd_path(char *cmd, t_env *env_list);

int			heredoc_run(t_redir *r, char **out_path, t_ms_state *st);
int			ap_prepare_heredocs(t_cmd *head, t_env *env);
int			ap_execute_line(t_cmd *line, t_env **penv);

int			status_from_wait(int st);

int			ap_spawn_all(t_pipe_ctx *ctx);

int			ap_streq(const char *a, const char *b);
int			ap_is_numeric_str(const char *s);
int			ap_is_valid_env_key(const char *s);
int			ap_is_parent_affecting_builtin(char **argv);

int			ap_err_msg(const char *cmd, const char *msg);
int			ap_err_msg(const char *cmd, const char *msg);
int			ap_err_msg_quoted(const char *cmd,
				const char *arg, const char *msg);
void		err_msg(const char *a, const char *b);
void		ms_puterr3(const char *a, const char *b, const char *c);
int			ms_is_numeric(const char *s);
long long	ms_atoll(const char *s);
int			ms_norm_code(long long v);
void		setup_signals_child(void);
int			ap_execute_line(t_cmd *line, t_env **penv);

void		ft_split_free(char **arr);
void		ms_request_exit(int code);
int			ms_exit_requested(void);
int			ms_get_exit_code(void);
void		safe_close(int fd);
void		ap_child_exit(int ec, t_cmd *cmd_head, t_env *env, pid_t *pids);

void		free_everything(t_env *env);
int			is_blank_line(const char *s);
void		run_one_command_line(char *one, t_env **penv);
int			has_newline(const char *s);
void		chomp_newline(char *s);
int			read_and_prepare_line(char **line, int interactive);
int			exec_line_or_error(char *line, t_env **penv);
void		shell_loop(t_env **penv);
int			cd_err(const char *msg);
char		*get_oldpwd_snapshot(t_env *env);
int			cd_chdir_and_update(t_env **penv, const char *path,
				char *oldpwd_heap);
int			cd_to_home(t_env **penv, char *oldpwd_heap);
int			cd_to_oldpwd(t_env **penv, char *oldpwd_heap);
int			ms_export_print_all(t_env *env);
int			ap_spawn_one(t_pipe_ctx *ctx);
int			ap_apply_one_redir(t_redir *r);

int			exit_req_store(int op, int value);
int			exit_code_store(int op, int value);
int			status_store(int op, int value);

void		try_exec_sh(char *path, char **envp);
int			is_directory(const char *p);
void		cmd_error(char *cmd, char *msg);
char		*prepare_exec_path(char **argv, t_env *env_list);
int			report_exec_error(char *path, char *cmd);
void		heredoc_child(t_hd_ctx *ctx);
int			open_tty_in(void);
void		hd_child_cleanup(t_hd_ctx *ctx);
int			hd_next_line(int fd_in, char **line);
int			hd_process_line(t_hd_ctx *ctx, int fd_in, char *line);
int			hd_child_open_in_or_exit(t_hd_ctx *ctx, int *fd_in);
int			hd_child_step(t_hd_ctx *ctx, int fd_in);
void		hd_child_finish(t_hd_ctx *ctx, int fd_in);
void		ms_sig_set(int signo);
int			ms_sig_get(void);
void		ms_sig_clear(void);
int			hd_is_name_start(char c);
int			hd_is_name_char(char c);
char		*hd_join2(const char *a, const char *b);
char		*hd_append_char(char *acc, char c);
char		*hd_append_str(char *acc, const char *s);
char		*hd_expand_dollar(const char *s, size_t *i, t_env *env);
char		*hd_expand_step(const char *s, size_t *i, t_env *env, char *acc);
char		*hd_expand_vars(const char *s, t_env *env);

#endif