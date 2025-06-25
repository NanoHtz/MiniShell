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
# include "structs.h"

//main.c
t_lexer	*init_mini(void);
void	loop(t_lexer *lxr, t_mini *shell);
void	clear_mini(t_lexer *lxr, t_mini *shell);
//debugs.c
void	debug_print_tokens(t_lexer *lxr);
void	debug_print_cmds(t_cmd *cmds);
void	debug_print_env(char **env, const char *label);
void	debug_print_expanded_cmds(t_cmd *cmds);
void	print_own_env2(char **own_env);
//todo ******************************utils.c***********************************
//env.c
char	**copy_env(char **envp);
//frees.c
void	free_cmd(t_cmd *cmd);
void	free_cmds(t_cmd *cmd);
void	free_args(char **argv);
//todo ******************************lexer.c***********************************
//lexer.c
void	lexer(t_lexer *lexer, const char *input);
void	init_lexer(t_lexer *lexer, const char *input);
//tokenizer.c
void	tokenizer(t_lexer *lexer);
int		token(t_lexer *lexer, t_token_type type, const char *text, int n);
t_token	*make_token(t_token_type type, const char *text);
//types.c
int		two_ops(t_lexer *lxr);
int		one_ops(t_lexer *lxr);
int		word_token(t_lexer *lxr);
//lexer_utils.c
int		is_delimiter(char c);
int		take_two(const char *line, int i, const char op);
//quotes.c
int		quotes(t_lexer *lxr);
int		copy_value(int len, int start, t_lexer *lxr);
//free_lexer.c
void	free_lexer(t_lexer *lxr);
void	clear_tokens(t_list *lst);
//todo ******************************parser.c***********************************
//parser.c
t_cmd	*parser(t_list *tokens);
int		run_parse(t_list *tokens, t_cmd *head, t_token_type *last);
int		add_arg(t_cmd *cmd, const char *value);
//parser_utils.c
t_rtype	take_type(t_token_type tt);
t_cmd	*new_cmd(void);
int		check_pipe_end(t_token_type last);
int		check_pipe_start(t_list *toklist);
//redir.c
int		ft_isredir(t_token_type type);
void	add_redir(t_cmd *cmd, t_redir *redir);
t_redir	*new_redir_node(t_rtype type, const char *target);
//handler.c
int		handle_word(t_list **node, t_cmd **cur);
int		handle_redir(t_list **node, t_cmd **cur);
int		handle_pipe(t_list **node, t_cmd **cur);
int		process_token(t_list **node, t_cmd **cur);
//todo ****************************variables*********************************
//vars.c
t_cmd	*vars(t_cmd	*cmds, t_mini *shell);
void	remove_vars_from_av(t_cmd *cmd);
t_cmd	*prune_empty_cmds(t_cmd *cmds);
void	handle_all_vars(t_cmd *cmd, t_mini *shell);
void	handle_partial_vars(t_cmd *cmd);
//vars_utils1.c
char	*get_key(const char *assign);
int		find_key_index(char **env, const char *key);
void	replace_entry(char **env, int index, const char *assign);
void	append_entry(char ***env, const char *assign);
int		count_valid_envs(char **av);
//vars_utils2.c
int		all_vars(char **av);
int		is_valid(const char *str);
void	update_env(char ***own_env, const char *assign);
void	remove_command(t_cmd *cmd);
void	set_cmd_env(t_cmd *cmd);
//vars_utils3.c
int		count_non_env_args(char **av);
//todo ****************************executor.c*********************************
//todo ****************************builtin.c**********************************
//builtin.c
void	builtin(t_cmd *cmds, t_mini *shell);
void	exec_builtin(t_cmd *cmd, t_mini *shell);
int		is_builtin(char *av);
//ft_echo.c
int		is_n(char *av);
void	ft_echo(t_cmd *cmd);
//ft_pwd.c
void	ft_pwd(void);
//ft_cd.c
void	ft_cd(t_cmd *cmd);
//ft_exit.c
int		ft_exit(t_cmd *cmd);
//ft_env.c
void	ft_env(t_cmd *cmd, char **env);
int		equal(char *str, char c);
//ft_unset.c
void	ft_unset(t_cmd *cmd, char **env);
void	remove_var(char *av, char **env);
int		validate(char *av);
//ft_export.c
void	ft_export(char **args, t_mini *shell);
//ft_export_utils.c
char	**copy_env_without_index(char **env, int index);
int		env_count(char **env);

#endif
