#ifndef MINISHELL_H
# define MINISHELL_H

# define S_QUOTE 39
# define D_QUOTE 34

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

typedef struct			s_list
{
    char    			*content;
    struct s_list		*next;
}						t_list;

struct					s_pipe
{
	int		nb_pipe;
	char	***all;
	int		(*fd)[2];
	int		pid;
	int		save;
	int		fd_saved;
};
typedef struct s_pipe	t_pipe;

struct                  s_redir
{
    int		left;
    int		right;
    char 	mode;
    char	*save_left;
    char 	*save_right;
};
typedef struct s_redir  t_redir;

struct                  s_cmd
{
    t_pipe  pipe;
    t_redir redir;
    pid_t	pid;
    char    **cmds;
    int 	mystdout;
    int 	mystdin;
};
typedef struct s_cmd    t_cmd;

struct 					s_space
{
	int 	size;
	int 	j;
	int 	in_quote;
	char 	*dest;
	char 	tmp;
};
typedef struct s_space	t_space;

int     	get_next_line(int fd, char **line, int option);
int     	ft_strlen(char *str);
int     	parsing_line(char *cmd, t_list **envs);
char    	**new_split(char *str, char c);
char    	*create_space_around(char *str);
int	 		ft_strcmp(char *s1, char *s2);
int     	free_parsing_line(char **av, char *line, int status);
void    	free_char_double_array(char **av);
void    	display_prompt(void);
int     	parsing_pipe(t_cmd *cmd);
void    	init_struct_cmd(t_cmd *cmd);
char		*ft_strdup(char *src);
int     	several_string(char **cmds);
int     	parsing_redir(t_cmd *cmd);
int     	count_string(char **cmds, char *str);
void    	ft_putstr_fd(char *str, int fd);
int     	errno_parsing_line(int index);
int     	check_first_command(t_cmd *cmd, t_list **envs);
t_list		*ft_lstnew(void *content);
void		ft_lstadd_back(t_list **alst, t_list *new);
void		ft_afflist(t_list **lst);
t_list      *init_list_env(char **envp);
int     	is_builtin(char *str);
char		*ft_stradd(char const *s1, char const *s2);
char	 	*get_path_command(char *command, t_list **envs, int option);
char	 	*get_env(t_list *list, char *str);
int			ft_strncmp(const char *s1, const char *s2, size_t n);
char 		**create_package(char **cmds, t_list **envs, int option);
void		ft_lstclear(t_list **lst, void (*del)(void *));
int 		free_8(char *str, t_list **envs, t_cmd *cmd, int ret);
int		 	free_i(t_cmd *cmd, int index);
char		*get_left(t_cmd *cmd);
char		*get_right(t_cmd *cmd);
int 		parse_redir_fd(t_cmd *cmd);
int 		exec_cmd(t_cmd *cmd, t_list **envs, int i);
int			mid_fork(t_cmd *cmd, t_list **envs, int i);
int			last_fork(t_cmd *cmd, t_list **envs, int i);
int			first_fork(t_cmd *cmd, t_list **envs, int i);
void		close_after(t_cmd *cmd, int index);
void		close_last(int index, int n, int (*fd)[2]);
void		close_first(int index, int n, int (*fd)[2]);
void		close_all(int index, int n, int (*fd)[2]);
int			init_pipe(t_cmd *cmd);
int			init_all_package(t_cmd *cmd, t_list **envs);
int 		parsing_quotes(t_cmd *cmd, t_list **envs);
char		*ft_strjoin(char const *s1, char const *s2);
char		*char_strjoin(char *str, char c);
char 		*double_quote(char *str, t_list **envs);
char 		*simple_quote(char *str);
char	 	*get_var_dollar(char *str, t_list **envs);
int			init_space(t_space *space, char *str);
int			get_size(char *str);
void		free_package(t_cmd *cmd);
int			sort_builtin(t_cmd *cmd, t_list **envs);
int			ft_pwd(t_cmd *cmd);
int			is_symbol(char *str);
int			ft_cd(t_cmd *cmd, t_list **envs);
void		set_env(t_list **envs, char *env, char *value);
int			ft_env(t_cmd *cmd, t_list **envs);
int			ft_unset(t_cmd *cmd, t_list **envs);
char		**list_to_array(t_list *envs);
int			free_end_pipe(t_cmd *cmd, int ret);
int			pipe_first_command(t_cmd *cmd, t_list **envs);

#endif