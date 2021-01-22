#include "minishell.h"

void    show_packages(t_cmd *cmd)
{
    int i;

    i = 0;
    while (cmd->cmds[i])
    {
        printf("[%s]\n", cmd->cmds[i]);
        i++;
    }
}

int     parsing_command(t_cmd *cmd, t_list *envs)
{
    if (!(check_first_command(cmd, envs)))
        return (0);
    //remove_quote();
}

int     parsing_line(char *command, char **envp)
{
    char    **cmds;
    t_list  *envs;
    t_cmd   cmd;

    init_struct_cmd(&cmd);
    if (!(number_quote_is_even(command)))
        return (ft_errno(-1));
    if (!(command = create_space_around(command)))
        return (ft_errno(-2));
    if (!(cmd.cmds = new_split(command, ' ')))
        return (ft_errno(-3));
    if (!several_string(cmd.cmds))
        return (ft_errno(-4));
    if (!parsing_pipe(&cmd))
        return (ft_errno(-5));
    if (!(parsing_redir(&cmd)))
        return (ft_errno(-6));
    if (!(envs = init_list_env(envp)))
        return (ft_errno(-7));
    //show_packages(&cmd);
    if (!(parsing_command(&cmd, envs)))
        return (-1);
    printf("All good\n");
    free(command);
    free_char_double_array(cmd.cmds);
    return (0);
}
