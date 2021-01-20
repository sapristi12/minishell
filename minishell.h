#ifndef MINISHELL_H
# define MINISHELL_H

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

int     get_next_line(int fd, char **line, int option);
int     ft_strlen(char *str);
int     parsing_line(char *cmd, char **envp);
char    **new_split(char *str, char c);
char    *create_space_around(char *str);
int	 	ft_strcmp(char *s1, char *s2);
int     free_parsing_line(char **av, char *line);
void    free_char_double_array(char **av);
void    display_prompt(void);
int     parsing_pipe(t_cmd *cmd);
void    init_struct_cmd(t_cmd *cmd);
int     create_args(t_cmd *cmd);
char	*ft_strdup(char *src);
int     several_string(char **cmds, char *str);
int     number_quote_is_even(char *str);
int     parsing_redir(t_cmd *cmd);
int     count_string(char **cmds, char *str);
int     several_string(char **cmds, char *str);

#endif