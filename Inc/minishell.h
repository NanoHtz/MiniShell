/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgalvez- <fgalvez-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 21:16:53 by fgalvez-          #+#    #+#             */
/*   Updated: 2024/12/05 15:09:58 by fgalvez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libs.h"
# include "unistd.h"
# include <fcntl.h>
# include "structs.h"
# include <sys/types.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include <signal.h>
# include <readline/readline.h>
# include <stdio.h>

extern int	g_interrupted;

//main.c
t_lexer	*init_mini(void);
void	ms_fix_shlvl(char ***penv);
void	run_cmds(t_cmd *cmds, t_mini *shell);
void	loop(t_lexer *lxr, t_mini *shell);
void	clear_mini(t_lexer *lxr, t_mini *shell);
//debugs.c
void	debug_print_tokens(t_lexer *lxr);
void	debug_print_cmds(t_cmd *cmds);
void	debug_print_env(char **env, const char *label);
void	debug_print_expanded_cmds(t_cmd *cmds);
void	print_own_env2(char **own_env);
void	debug_exec_plan(const t_cmd *cmds);
void	debug_tokens(t_list *tokens);
//todo ******************************utils.c***********************************
//env.c
char	**copy_env(char **envp);
//frees.c
void	free_cmd(t_cmd *cmd);
void	free_cmds(t_cmd *cmd);
void	free_args(char **argv);
void	free_loop(t_lexer *lxr, t_cmd	*cmds, char *line);
//count_commands.c
int		count_commands(t_cmd *cmds);
//status.c
int		syntax_error(t_mini *sh, const char *tok);
int		syntax_error_unclosed_quote(t_mini *sh, char quote);
void	handle_command_not_found(t_cmd *cmd, char **exec_env);
void	handle_directory_error(t_cmd *cmd, char **exec_env);
void	handle_execve_error(char *cmd_name, char **exec_env);
//todo ******************************lexer.c***********************************
//lexer.c
void	lexer(t_lexer *lexer, const char *input);
void	init_lexer(t_lexer *lexer, const char *input);
//tokenizer.c
void	tokenizer(t_lexer *lexer);
int		token(t_lexer *lexer, t_token_type type, const char *text, int n);
int		skip_token(t_lexer *lexer, t_token_type type, const char *text, int n);
int		push_token(t_lexer *lexer, t_token_type type, const char *text);
t_token	*make_token(t_token_type type, const char *text);
//quotes.c
int		quotes(t_lexer *lxr);
int		copy_value(int len, int start, t_lexer *lxr, int s_q);
int		unclosed_quote(t_lexer *lxr, char quote);
//types.c
int		two_ops(t_lexer *lxr);
int		two_ops_more(t_lexer *lxr);
int		word_token(t_lexer *lxr);
//one_ops.c
int		one_ops(t_lexer *lxr);
int		one_ops_more(t_lexer *lxr);
int		one_ops_more_2(t_lexer *lxr);
//lexer_utils.c
int		is_delimiter(char c);
int		take_two(const char *line, int i, const char op);
int		take_three(const char *line, int i, char op);
//free_lexer.c
void	free_lexer(t_lexer *lxr);
void	clear_tokens(t_list *lst);
//todo ******************************parser.c***********************************
//parser.c
t_cmd	*parser(t_list *tokens, t_mini *shell);
int		run_parse(t_list *tokens, t_cmd *head,
			t_token_type *last, t_mini *shell);
//checks_preparser.c
int		sintax_ops(t_list *toks, t_mini *sh);
int		sintax_redir(t_list *toks, t_mini *sh);
int		pipe_space_pipe(t_list *toks, t_mini *sh);
// int		pipeline_segments(t_list *toks, t_mini *sh);
int		check_pipe_end(t_token_type last, t_mini *sh);
//checks_utils.c
int		validate_redir_target(t_mini *sh, t_list *nx);
void	update_flags(t_token_type type, int *saw_cmd, int *prev_was_redir);
//more_checks_utils.c
int		consume_redirs_after_pipe(t_list **node, t_mini *sh);
int		error_value_or_newline_ptr(t_mini *sh, t_token *tok);
int		error_value_or_newline_strict(t_mini *sh, t_token *tok);
//process_token.c
int		process_token(t_list **node, t_cmd **cur, t_mini *shell);
int		handle_word(t_list **node, t_cmd **cur, t_mini *shell);
int		handle_redir(t_list **node, t_cmd **cur, t_mini *shell);
int		handle_pipe(t_list **node, t_cmd **cur);
//process_token_utils.c
t_redir	*last_redir_node(t_redir *lst);
t_list	*last_or_self(t_list *candidate, t_list *self);
//handler_word_utils.c
int		skip_unquoted(char *acc, int had_quote, t_list **node, t_list *last);
void	scan_following_span(t_list *it_start, t_list **last, int *had_quote);
int		add_arg(t_cmd *cmd, const char *value);
char	**grow_argv(t_cmd *cmd);

//handler_redir_utils.c
int		redir_setup(t_list **node, t_rtype *rt, t_token **tok);
char	*expand_first_piece_node(t_list *node, t_cmd *cur, t_mini *shell);
t_list	*span_last_joinable(t_list *start);
void	add_redir(t_cmd *cmd, t_redir *redir);
t_redir	*new_redir_node(t_rtype type, const char *target);
//more_redir_utils.c
int		redir_expect_operand(t_list **node, const char *op, t_token **out_tok);
int		redir_syntax_err(const char *op);
int		ft_isredir(t_token_type type);
//handler_utils.c
int		append_next_piece(char **acc, t_token *tok, t_cmd *cur, t_mini *shell);
int		append_span(char **acc, t_list *start, t_cmd *cur, t_mini *shell);
int		is_joinable_token(t_token *tok);
//parser_utils.c
t_rtype	take_type(t_token_type tt);
t_cmd	*new_cmd(void);
int		is_redir(t_token_type t);
int		is_wordish(t_token_type t);
//todo ****************************variables*********************************
//vars.c
t_cmd	*vars(t_cmd	*cmds, t_mini *shell);
void	handle_all_vars(t_cmd *cmd, t_mini *shell);
void	handle_partial_vars(t_cmd *cmd);
int		all_vars(char **av);
//update_envs.c
void	update_env(char ***own_env, const char *assign);
void	set_cmd_env(t_cmd *cmd);
//remove_vars.c
void	remove_command(t_cmd *cmd);
void	remove_vars_from_av(t_cmd *cmd);
void	remove_node(t_cmd **head, t_cmd *target);
//key_and_entrys.c
char	*get_key(const char *assign);
int		find_key_index(char **env, const char *key);
void	replace_entry(char **env, int index, const char *assign);
void	append_entry(char ***env, const char *assign);
//vars_utils.c
int		count_valid_envs(char **av);
int		is_valid(const char *str);
int		count_non_env_args(char **av);
//last_status.c
int		last_status(char **av);
char	*expand_last_status_in_str(const char *src, int last_status);
int		push_char(char **out, char c);
char	*join_free_first(char *a, const char *b);
//more_vars.c
int		loop_expand(const char *src, char **out, const char *status, int st[3]);
int		join_status(char **out, const char *status);
int		is_quote_char(char ch, int sq, int dq);
void	toggle_quotes(char ch, int *sq, int *dq);
int		should_expand(const char *s, int i, int sq);
//todo ****************************expands.c*********************************
//command_expands.c
char	*extract_var(char *str, char **cmd_env, t_mini *shell, int *var_len);
int		scan_var_name(const char *var);
char	*extract_named_var(const char *var, int j, t_mini *shell, int *var_len);
char	*handle_qmark(t_mini *shell, int *var_len);
char	*get_env_value(char *key, char **cmd_env, char **own_env, char **envp);
//expands_utils.c
char	*expand(char *command, char **env);
char	*find_unquoted_dollar(const char *s);
int		toggle_dquote(char c, int *dq, int sq);
int		toggle_squote(char c, int *sq, int dq);
int		is_valid_dollar_start(unsigned char c);
//more_expands_utils.c
t_cmd	*expand_commands(t_cmd *cmds, t_mini *shell);
char	*look_for_expands(char *str, char **cmd_env, t_mini *shell);
char	*expand_line_heredoc(const char *s, char **cmd_env, t_mini *shell);
//expands.c
char	*expand_piece(t_token_type type, const char *val,
			char **cmd_env, t_mini *shell);
char	*expand_all(const char *s, char **cmd_env, t_mini *shell);
//handlers.c
size_t	var_name_len(const char *p);
int		xcat_take(char **dst, char *right);
char	*cat_free_left(char *left, const char *right);
int		needs_process(const char *s);
char	*join_free(char *a, char *b);
//more_utils.c
size_t	var_name_len(const char *p);
ssize_t	append_name_at(char **out, const char *p,
			char **cmd_env, t_mini *shell);
//todo ****************************executor.c*********************************
//run_cmds.c
void	run_cmds(t_cmd *cmds, t_mini *shell);
int		count_commands(t_cmd *cmds);
//execute_commands.c
void	execute_commands(t_cmd *cmds, t_mini *shell);
pid_t	process_command(t_cmd *cmd, int *in_fd, t_mini *shell);
void	child_process(t_cmd *cmd, int in_fd, int fd[2], t_mini *shell);
void	parent_process(pid_t pid, t_cmd *has_next, int *in_fd, int fd[2]);
void	wait_for_children(pid_t last_pid, t_mini *shell);
//heredoc_utils.c
int		handle_write_error(char *line, int pipefd[2]);
void	warn_delimiter_eof(const char *delimiter);
int		heredoc_eof_handler(const char *delimiter, char *line, int pipefd[2]);
int		heredoc_delim_found(int pipefd[2]);
int		wait_heredoc(int *pipefd, pid_t pid, t_mini *shell);
//heredoc.c
int		handler_heredoc(t_redir *r, char **cmd_env, t_mini *shell);
int		hdoc_loop_iter(char **line, size_t *len,
			int pipefd[2], t_hdoc_ctx *ctx);
void	run_heredoc_loop(t_redir *r, int write_fd, char **env, t_mini *shell);
//path_process.c
char	*get_command_path(char *cmd, char **envp);
char	*search_in_paths(char *cmd, char **paths);
char	*try_direct_path(char *cmd);
char	**get_env_paths(char **envp);
//handle_redirections.c
int		handle_redirections(t_cmd *cmd);
//redirections.c
int		redir_heredoc(t_redir *r, t_cmd *cmd, t_mini *shell);
int		redir_append(t_redir *r);
int		redir_write(t_redir *r);
int		redir_read(t_redir *r);
int		handle_heredoc_redir(t_redir *r);
//execute_utils.c
pid_t	while_redir(t_cmd *cmd, t_mini *shell);
char	**free_charpp(char **v);
int		connect_pipes(int in_fd, int fd[2], t_cmd *cmd);
char	**build_and_check_env(t_mini *shell, t_cmd *cmd);
void	handle_builtin(t_cmd *cmd, t_mini *shell, char **exec_env);
//keys.c
size_t	charpp_len(char **v);
size_t	keylen(const char *s);
int		same_key(const char *a, const char *b);
int		process_valid_entry(char **res, char *ov, size_t *r);
int		process_overlay_entries(char **overlay, char **res,
			size_t no, size_t *r);
//more_utils.c
int		is_directory(char *path);
int		handle_redirections_check(t_cmd *cmd);
char	**build_exec_env(char **base, char **overlay);
//todo ****************************builtin.c**********************************
//builtin.c
void	builtin(t_cmd *cmds, t_mini *shell);
int		exec_builtin(t_cmd *cmd, t_mini *shell);
int		is_builtin(char *av);
//ft_echo.c
int		is_n(char *av);
int		ft_echo(t_cmd *cmd);
//ft_pwd.c
void	ft_pwd(void);
//ft_cd.c
int		ft_cd(t_cmd *cmd, t_mini *shell);
int		cd_change_dir(const char *target, char **old, char **now);
int		env_normi(t_mini *shell, const char *name,
			const char *errmsg, char **out);
int		cd_get_target(t_cmd *cmd, t_mini *shell, char **out, int *print_new);
//cd_utils.c
void	ms_setenv(t_mini *shell, const char *key, const char *val);
char	*ms_getenv_dup(t_mini *shell, const char *key);
//ft_exit.c
int		ft_exit(t_cmd *cmd, t_mini *shell);
//ft_env.c
int		ft_env(t_cmd *cmd, char **env);
int		equal(char *str, char c);
//ft_unset.c
int		ft_unset(t_cmd *cmd, char **env);
void	remove_var(char *av, char **env);
int		validate(char *av);
//ft_export.c
int		ft_export(char **args, t_mini *shell);
//ft_export_utils.c
char	**copy_env_without_index(char **env, int index);
int		env_count(char **env);
void	ms_export_err_ident(const char *arg);
int		ms_is_valid_ident(const char *s);
int		is_underscore_entry(const char *s);
//print_export.c
void	print_export_no_args(char **env);
//utils.c
char	**dup_env(char **env);
void	sort_strings(char **a);
//todo *********************signal.c******************************
//signal.c
void	sigint_heredoc_handler(int sig);
void	sigint_prompt_handler(int sig);
void	setup_signals(void);

#endif
