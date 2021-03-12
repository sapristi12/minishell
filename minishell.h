/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erlajoua <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/11 15:07:04 by erlajoua          #+#    #+#             */
/*   Updated: 2021/03/12 13:11:03 by erlajoua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# define S_QUOTE 39
# define D_QUOTE 34
# define SLASH 92

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <string.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include <fcntl.h>
# include <errno.h>
# include <limits.h>
# include <signal.h>
# include <dirent.h>

enum						e_getpid
{
	GET,
	SET
};

typedef struct				s_list
{
	char				*content;
	struct s_list		*next;
}							t_list;

struct						s_pipe
{
	int		nb_pipe;
	char	***all;
	int		(*fd)[2];
	int		pid;
	int		save;
	int		fd_saved;
};
typedef struct s_pipe		t_pipe;

struct						s_redir
{
	int		left;
	int		right;
	char	mode;
	char	*save_left;
	char	*save_right;
};
typedef struct s_redir		t_redir;

struct						s_cmd
{
	t_pipe		pipe;
	t_redir		redir;
	pid_t		pid;
	t_list		*exported;
	char		**cmds;
	int			mystdout;
	int			mystdin;
	int			exit_status[2];
	int			**tab;
	int			*tabpid;
	int			tabsize;
	int			i;
};
typedef struct s_cmd		t_cmd;

struct						s_space
{
	int		size;
	int		j;
	int		in_quote;
	char	*dest;
	char	tmp;
};
typedef struct s_space		t_space;

struct						s_quo
{
	int		in_quote;
	char	tmp;
};
typedef struct s_quo		t_quo;

struct						s_prompt
{
	int		i;
	int		in_quote;
	int		flag;
	char	tmp;
};
typedef struct s_prompt		t_prompt;

struct						s_split
{
	char	**dest;
	int		i;
	int		in_quote;
	char	tmp;
};
typedef struct s_split		t_split;

int			g_sig;

long long					ft_llatoi(char *str);
t_list						*sort_list(t_list *lst, int (*cmp)(char *, char *));
t_list						*ft_lstnew(void *content);
t_list						*init_list_env(char **envp);
int							get_next_line(int fd, char **line, int option);
int							ft_strlen(char *str);
int							parsing_line(char *prompt, t_list **envs,
							t_cmd *cmd);
char						**new_split(char *str, char c);
void						check_quote(char **str, char c,
							int *in_quote, char *tmp);
char						*my_strdup(char *str, int size);
char						*create_space_around(char *str);
int							ft_strcmp(char *s1, char *s2);
int							free_parsing_line(char **av, int status);
void						free_char_double_array(char **av);
void						display_prompt(void);
int							parsing_pipe(t_cmd *cmd);
void						init_struct_cmd(t_cmd *cmd);
char						*ft_strdup(char *src);
int							several_string(char **cmds);
int							parsing_redir(t_cmd *cmd, int index);
int							count_string(char **cmds, char *str);
void						ft_putstr_fd(char *str, int fd);
int							errno_parsing_line(int index);
int							check_first_command(t_cmd *cmd, t_list **envs);
void						ft_lstadd_back(t_list **alst, t_list *new);
void						ft_afflist(t_list **lst);
int							is_builtin(char *str);
char						*ft_stradd(char const *s1, char const *s2);
int							get_path_command(char *command, t_list **envs);
char						*t_get_path_command(char *command, t_list
							**envs, int option);
int							t_ft_dir(char *path, char *exec);
char						*get_env(t_list *list, char *str);
int							ft_strncmp(const char *s1, const char
							*s2, size_t n);
char						**create_package(char **cmds, t_list
							**envs, int *tab);
void						ft_lstclear(t_list **lst, void(*del)(void*));
int							free_8(char *str, t_cmd *cmd, int ret);
int							free_i(t_cmd *cmd, int index);
char						*get_left(t_cmd *cmd, int index);
char						*get_right(t_cmd *cmd, int index);
int							parse_redir_fd(t_cmd *cmd, int index, int *tab);
int							exec_cmd(t_cmd *cmd, t_list **envs, int i);
int							mid_fork(t_cmd *cmd, t_list **envs, int i);
int							last_fork(t_cmd *cmd, t_list **envs, int i);
int							first_fork(t_cmd *cmd, t_list **envs, int i);
void						close_after(t_cmd *cmd, int index);
void						close_last(int index, int n, int (*fd)[2]);
void						close_first(int index, int n, int (*fd)[2]);
void						close_all(int index, int n, int (*fd)[2]);
int							init_pipe(t_cmd *cmd);
int							init_all_package(t_cmd *cmd, t_list **envs);
int							parsing_quotes(t_cmd *cmd, t_list **envs);
char						*ft_strjoin(char const *s1, char const*s2);
char						*char_strjoin(char *str, char c);
char						*double_quote(char *str, t_list **envs);
char						*simple_quote(char *str);
int							init_space(t_space *space, char *str);
void						free_package(t_cmd *cmd);
int							sort_builtin(t_cmd *cmd, t_list **envs, int index);
int							ft_pwd(void);
int							is_symbol(char *str);
int							ft_cd(t_cmd *cmd, t_list **envs);
void						set_env(t_list **envs, char *env, char *value);
int							ft_env(t_cmd *cmd, t_list **envs);
int							ft_unset(t_cmd *cmd, t_list **envs);
char						**list_to_array(t_list *envs);
int							free_end_pipe(t_cmd *cmd, int ret);
int							pipe_first_command(t_cmd *cmd, t_list **envs);
char						*normal_quote(char *str, t_list **envs);
int							free_error_redir(t_cmd *cmd, int ret);
char						*get_tilde_path(char *str, t_list **envs);
int							ft_echo(t_cmd *cmd, int index);
int							ft_exit(t_cmd *cmd);
int							is_token_last(t_cmd *cmd);
int							is_token_char (char c);
void						signal_handle(void);
int							ft_export(t_cmd *cmd, t_list *envs);
void						ft_affexport(t_list **lst);
char						*create_env(char *str);
int							is_there_char (char *str, char c);
int							is_alpha(char c);
char						**pointer_package(char **cmds, int index);
int							free_quote(t_cmd *cmd, char *prompt, int index);
char						*remove_escaped_token(char *str);
int							loop_command_pipe(t_cmd *cmd, t_list **envs);
int							transform_token(t_cmd *cmd);
int							is_even_quote(char *str);
char						*create_new_str(char *str, t_list **envs);
int							move_normal_pointer(char *str);
int							move_pointer(char *str, char tmp);
char						*get_var_dollar(char *str, t_list **envs);
void						apply_tmp(char *tmp, char c, int *in_quote);
int							get_size(char *str);
int							normal_slash(char **new, char c);
int							count_string2(char **cmds, char *str, int *tab);
int							move_pointer_i(char **cmds);
int							only_spaces(char *str);
void						free_int_double_array(t_cmd *cmd);
void						init_split(t_split *spl);
char						*deux_strdup(char *src);
void						condition_display(t_cmd *cmd, char *prompt);
void						is_command_nf(t_cmd *cmd, t_list **envs);
void						is_not_found(char *cmd, char **envp);
void						multiple_semi3(char *str, int i,
							char *tmp, int *in_quote);
int							next_dollar(char c);
int							only_zeros(char *str);
int							export_list(t_list *envs, t_list *exported);
int							check_prompt(int index, char *prompt);
int							init_tab(t_cmd *cmd);
int							*create_tab_index(char **cmds);
int							get_flag(int op, int val);
int							get_dup(int op, int val);
int							error_identifier(char *str);
int							is_num(char c);
int							multiple_semi1(char *str, int *flag, int *j);
int							multiple_semi2(char *str, int *j);
int							main_loop(char *prompt, t_cmd *cmd, t_list **envs);
int							is_first_condition(char tmp, char now,
							char bef, char bef2);
int							is_dir(char *cmd, int option);
int							is_space(char *str);
int							only_equal(char *str);
void						exported_list(t_cmd *cmd, int i);
t_list						*init_none(void);
int							condition_u(char *content, char *str, int index);
void						ft_delone(t_list **lst, char *str, int index);
char						*get_env2(t_list **envs, char *str);
int							is_notidentifier(char *str);
void						hub_join_not_found(char *str);

#endif
