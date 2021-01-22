#ifndef MINISHELL_H
# define MINISHELL_H

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
    int left;
    int right;
};
typedef struct s_redir  t_redir;

struct                  s_cmd
{
    t_pipe  pipe;
    t_redir redir;
    char    **cmds;
};
typedef struct s_cmd    t_cmd;

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

int     	get_next_line(int fd, char **line, int option);
int     	ft_strlen(char *str);
int     	parsing_line(char *cmd, char **envp);
char    	**new_split(char *str, char c);
char    	*create_space_around(char *str);
int	 		ft_strcmp(char *s1, char *s2);
int     	free_parsing_line(char **av, char *line);
void    	free_char_double_array(char **av);
void    	display_prompt(void);
int     	parsing_pipe(t_cmd *cmd);
void    	init_struct_cmd(t_cmd *cmd);
char		*ft_strdup(char *src);
int     	several_string(char **cmds);
int     	number_quote_is_even(char *str);
int     	parsing_redir(t_cmd *cmd);
int     	count_string(char **cmds, char *str);
void    	ft_putstr_fd(char *str, int fd);
int     	ft_errno(int index);
int     	check_first_command(t_cmd *cmd, t_list *envs);
t_list		*ft_lstnew(void *content);
void		ft_lstadd_back(t_list **alst, t_list *new);
void		ft_afflist(t_list *lst);
t_list      *init_list_env(char **envp);
int     	is_builtin(char *str);
char		*ft_stradd(char const *s1, char const *s2);
char	 	*get_path_command(char *command, t_list *envs);
char	 	*get_env(t_list *list, char *str);
int			ft_strncmp(const char *s1, const char *s2, size_t n);
char 		**create_package(char **cmds, t_list *envs);

#endif