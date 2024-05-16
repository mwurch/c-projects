/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpodack <rpodack@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/05 14:54:03 by rpodack           #+#    #+#             */
/*   Updated: 2023/11/05 14:54:03 by rpodack          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# define PIPE 1
# define EXEC 2
# define REDIR 3
# define WHITESPACE "\f\r\n\t\v "
# define TERMSIGN "<>|"
# define REDIRSIGN "<>"
# define QUOTESIGN "'\""
# define DOLLARSIGN "$"
# define _POSIX_C_SOURCE 200809L

# include <signal.h>
# include <sys/wait.h>
# include <sys/types.h>
# include <stdio.h>
# include <stdlib.h>
# include <stddef.h>
# include <unistd.h>
# include <string.h>
# include <errno.h>
# include <fcntl.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <linux/limits.h>
# include "../libft/libft.h"
# include "./get_next_line.h"
# include <sys/ioctl.h>

extern volatile sig_atomic_t	g_signal_received;

extern volatile sig_atomic_t	g_signal_received;

typedef struct s_env
{
	char			*full_line;
	char			*var;
	char			*value;
	struct s_env	*next;
}	t_env;

typedef struct s_node
{
	int	type;
}t_node;

typedef struct s_lsts
{
	t_env				*envlist;
	t_env				*env_exp;
	t_env				*curr;
	char				*prompt;
	char				*line;
	t_node				*node;
	char				**builds;
	int					changed;
	long unsigned int	j;
	char				*curr_path;
	char				*fut_path;
	int					*exit;
	int					flag_for_exit;
	int					flag_for_ctrlc;
	int					i;
	char				*tmp;
	int					temp;
	char				*ret;
	char				*home;
	char				sign;
	int					here_flag;
}	t_envl;

typedef struct s_exec
{
	int		type;
	char	**argv;
}t_exec;

typedef struct s_redir
{
	int				type;
	char			*file;
	int				fd;
	int				mode;
	struct s_node	*cmd;
}t_redir;

typedef struct s_pipe
{
	int				type;
	struct s_node	*left;
	struct s_node	*right;
}t_pipe;

char	*get_right_path(t_envl *env, t_exec *cmd);
int		test_tilde(char *s);
void	init_sig(void);
void	minishell(t_envl *env);
char	*get_promt(void);
void	err_minishell(t_envl *env);
t_node	*pipenode(t_node *left, t_node *right);
t_node	*execnode(void);
t_node	*redirnode(t_node *cmd, char *file, int mode, int fd);
char	*expand_that(char *args, t_envl *env);
int		check(char *s);
void	go_to_redir(char **str);
char	get_token(char **str);
char	*get_filename(char **str);
t_node	*get_redirnode(t_node *cmd, char *fn, char mod);
char	*append_rest_in_dollar(char *var, char *args);
char	*my_ft_substr(char *str, int start, int end);
void	skip_whitespace(char **str);
void	goto_next_arg(char **str);
int		cmd_length(char *str);
void	copy_over_append_rest(char *var, char *ret, \
char *args, int len_arg_to_delimiter);
void	skip_redir(char **str);
char	*go_through_args(char **args, t_envl *env, char *var, int i);
int		cmd_and_flag_count(char *str);
int		check_for_question(char **args);
int		write_argv(char **argv, char **s, t_envl *env);

char	**get_argv(char **s, t_envl *env);
t_node	*execpars(char **s, t_envl *env);

t_node	*pipepars(char **s, t_envl *env);
t_node	*parsestr(char **s, t_envl *env);
t_node	*parser(char *str, t_envl *env);
int		check_for_redir(char *s);

char	**get_argv(char **s, t_envl *env);
t_node	*execpars(char **s, t_envl *env);

t_node	*pipepars(char **s, t_envl *env);
t_node	*parsestr(char **s, t_envl *env);
t_node	*parser(char *str, t_envl *env);
int		check_for_redir(char *s);
void	reinit_c(void);
void	free_twod_array(char **arr);
void	free_tree(t_node *cmd);
void	free_exec(t_exec *cmd);
void	free_pipe(t_pipe *cmd);
void	free_redir(t_redir *cmd);
void	free_return(t_envl *env);
char	*my_ft_substr(char *str, int start, int end);
void	skip_whitespace(char **str);
void	goto_next_arg(char **str);
int		cmd_length(char *str);
void	do_skipping(char **s);
void	print_echo(char **str, int i, int flag, t_envl *env);
char	*dollar_dollar_bill_yaa(char *str, t_envl *env);
char	*trim_dollar(char *str);
void	handle_sigquit_default(void);
void	handle_sigint_default(void);
void	handle_sigint_ignore(void);
void	runcmd(t_node *cmd, t_envl *env, t_node *tree);
char	*do_it(char **args, t_envl *env, int *i, char *var);
void	do_redir(t_redir *node, t_envl *env, t_node *tree);
void	do_pipe(int *p, t_pipe *pnode, t_envl *env, t_node *tree);
void	do_exec(t_exec *ecmd, t_envl *env, t_node *tree);
char	**recreate_env(t_envl *env);

char	**get_paths(t_envl *env, char *cmd);

char	*get_here_doc(char **str);
int		my_strncmp(const char *s1, const char *s2, size_t n);

int		quote_str_len(char *s, t_envl *env);
int		check_quotes(char *s);

char	*get_quote_str(char *s, t_envl *env);

int		my_fork( t_envl *env, t_node *tree);
int		my_dup2(int old_fd, int new_fd, t_envl *env, t_node *tree);
void	free_after_open_error(t_envl *env, t_node *tree);
void	get_right_path_error(t_envl *env, t_node *tree);
void	error_after_pipe(t_envl *env, t_node *tree);
t_envl	*init_envlists(t_envl *env, char **envi);
int		check_for_spaceonly_str(char *s);
void	init_nullptr(t_envl *env);
void	do_redir_inparent(t_redir *node, t_envl *env, t_node *tree);
void	redir_inparent_util(t_envl *env);
void	process_dollar_sign_normal(t_env *env, char **s, int *count);
char	*get_home_env(t_envl *env, char *s);
void	increase_shlvl(t_env *env);
int		process_quote_arg(char *s, char **argv, t_envl *env, int *i);
void	process_home_env_logic(char **argv, t_envl *env, int *i, char *s);
void	process_dollar_logic(char **argv, char *s, t_envl *env, int *i);
int		more_than_one(char *str);
int		process_default_logic(char *s, char **argv, int *i, t_envl *env);
int		process_arguments(char **argv, char **s, t_envl *env, int *i);
void	handle_prompt(t_envl *env);
int		create_here_doc_file(int *fd, char *del, size_t *del_len, char **ret);
void	clean_up_here_doc(int fd, char *ret);
int		write_in_here_doc(int fd, size_t del_len, char *del, char *ret);
void	do_normal_dollar_sign(char **s, char *ret, int *ret_index, t_envl *env);
int		process_filename(char mod, char **filename, char *s, t_node *cmd);
t_node	*redirpars(t_node *cmd, char *s);
void	proc_nonquoted(t_envl *env, char **s, int *count);
void	wait_for_children(int *p, int *pid, t_envl *env);
void	wait_for_child_exit(t_envl *env, int pid, t_node *tree);
void	execve_error_handling(t_envl *env, t_node *tree, char **envdp);
void	execve_error_parent(t_node *tree, t_envl *env, char **envdp);
void	do_exec_inparent(t_exec *ecmd, t_envl *env, t_node *tree);
void	do_exec_util(t_exec *ecmd, t_envl *env, t_node *tree);
void	call_execve(t_exec *ecmd, t_envl *env, t_node *tree, char	**envdp);
char	*process_filling(char **args, t_env *curr, char *var, int i);
char	*catch_error(char **args);
int		check_for_dollar(char *s);
int		check_line(t_envl *env);
int		print_out(int flag, char *str, int count, t_envl *env);
void	process_normal_char(char **s, int *ret_index, char *ret, t_envl *env);
void	do_quoted_string(char **s, char *ret, int *ret_index, t_envl *env);
void	write_ret(char *ret, int *ret_index, char *str);
void	shlvl(t_envl *env);
int		my_fork1(t_node *tree);
int		my_dup21(int old_fd, int new_fd, t_node *tree);
int		free_after_open_error1(t_node *tree);
char	*process_filling(char **args, t_env *curr, char *var, int i);
char	*catch_error(char **args);
int		check_for_dollar(char *s);

/*buildins*/
void	runcmd_inparent(t_node *cmd, t_envl *env, t_node *tree);
void	do_exec_inparent(t_exec *ecmd, t_envl *env, t_node *tree);
void	do_pipe_inparent(int *p, t_pipe *pnode, t_envl *env, t_node *tree);
void	do_redir_inparent(t_redir *node, t_envl *env, t_node *tree);
int		count_argv(char **argv);
int		check_for_pipe(char *line);
int		check_for_buildins(t_exec *ecmd, t_envl *env);
void	call_build(t_exec *emcd, t_envl *env);
void	ft_pwd(t_envl *env);
void	ft_cd(char *str, t_envl *env);
char	*go_home(char *str, t_envl *env, char *curr_path, char *fut_path);
char	*putabspath(char *fut_path, char *curr_path, char *str, t_envl *env);
char	*get_ret(t_envl *env);
char	*go_to_oldpwd(t_envl *env);
char	*ft_home_user(char *str, t_envl *env);
void	update_pwds(t_envl *env, char *curr_path, char *future_path);
char	*fill_new_full(t_env *curr);
char	*gone_dir(char *fut_path, char *curr_path, char *str, t_envl *env);
int		specialheardoccase(t_envl *env, char **argv, int *i);
void	ft_echo(char **str, t_envl *env);
char	*append_rest(char *var, char *args);
char	*cream(char *str, t_envl *env);
size_t	ft_strlen_till_equal(char *args);
int		flag_or_not(char *str);
void	init_value_line(int size, int i, char *var, t_env *tmp);
void	update_value_util(int i, char *var, t_env *curr);
void	add_to_env_exp(char *var, t_envl *env);
void	ft_exit(char *exitstatus, t_envl *env);
void	ft_env(t_env **envlist, char **argv, t_envl *env);
t_env	*print_env(t_env *envlist);
void	ft_export(t_envl *env, char **var);
char	*ft_return(char *var, t_env *curr);
void	print_exp(t_env *env_exp);
void	add_to_lists(t_envl *env, char *var);
void	init_other_lines(t_env *tmp, char *var);
int		does_var_exist(t_envl *env, char *var, int lenvar);
void	update_value(char *var, t_env *curr, int lenvar);
int		ft_lenvar(char *var);
int		is_valid_entry(char *var);
void	find_node_in_exp(t_env *env_exp, char *var, int lenvar);
void	insert_to_exp(t_env **env_exp, t_env *tmp2);
void	init_ints(t_envl *env);
void	sort_env(char **env);
void	ft_unset(t_env *envlist, t_env *env_exp, char **to_unset, t_envl *env);
int		specialheardoccase(t_envl *env, char **argv, int *i);

/*utils env*/
int		ft_len(char **env);
int		ft_strcmp(const char *s1, const char *s2);
void	search_and_destroy(char *to_unset, t_env *envlist, t_env *env_exp);
void	del_next_node(t_env *curr);

/*env*/
t_envl	*init(char **envi, int *ex);
t_env	*init_env(char **env);
void	init_value(char *env, int i, t_env *tmp);
void	fill_list(char *env, t_env *tmp);
void	del_node_(t_env *env_exp);

/*list functions*/
t_env	*ft_lstnew_e(void);
void	ft_lstadd_back_e(t_env **lst, t_env *new);
void	ft_lstadd_front_e(t_env **lst, t_env *new);
t_env	*ft_lstlast_e(t_env *lst);
int		ft_lstsize_e(t_env *lst);

/*signals*/
void	ctrl_nichts(int sig);
void	ctrl_d(t_envl *env);
void	ctrl_c(int sig);
void	chld(int sig);

/*free*/
void	free_twod_array(char **arr);
void	free_env(t_envl *env);
void	ft_freelst(t_env *list);
void	free_tree(t_node *cmd);
void	free_node(t_env *curr);

void	free_both(char **builds, char **cmd);

#endif
