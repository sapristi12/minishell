#ifndef MINISHELL_H
# define MINISHELL_H

struct					s_parse
{
	int		nb_pipe;
	char	***all;
	int		(*fd)[2];
	int		pid;
	int		save;
	int		fd_saved;
};
typedef struct s_parse	t_parse;

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
int		ft_strcmp(char *s1, char *s2);
int     free_parsing_line(char **av, char *line);

#endif