#include "minishell.h"

void    swap(char **a, char **b)
{
	char 	*tmp;

	tmp = *a;
	*a = *b;
	*b = tmp;
}

t_list        *sort_list(t_list *lst, int (*cmp)(char *, char *))
{
	t_list    *begin;
	t_list    *p;

	begin = lst;
	while (lst)
	{
		p = lst->next;
		while (p)
		{
			if ((*cmp)(lst->content, p->content) > 0)
				swap(&lst->content, &p->content);
			p = p->next;
		}
		lst = lst->next;
	}
	return (begin);
}