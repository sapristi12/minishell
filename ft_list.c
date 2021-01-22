#include "minishell.h"

void	ft_afflist(t_list *lst)
{
    while (lst != NULL)
    {
        ft_putstr_fd(lst->content, 1);
        ft_putstr_fd("\n", 1);
        lst = lst->next;
    }
}

void	ft_lstadd_back(t_list **alst, t_list *new)
{
    t_list	*begin;

    if (new)
    {
        if (!(*alst))
            *alst = new;
        else
        {
            begin = *alst;
            while (begin->next)
                begin = begin->next;
            begin->next = new;
        }
    }
}

t_list		*ft_lstnew(void *content)
{
    t_list *list;

    list = malloc(sizeof(t_list));
    if (!list)
        return (NULL);
    list->content = content;
    list->next = NULL;
    return (list);
}