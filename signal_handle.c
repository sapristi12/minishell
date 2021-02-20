#include "minishell.h"

void 	signal_int(int signo)
{
	if (signo == SIGINT)
	{
		ft_putstr_fd("\n", 1);
		display_prompt();
	}
	g_sig = 128 + signo;
}


void 	signal_quit(int signo)
{
	if (signo == SIGQUIT)
	{
		ft_putstr_fd("Quit : (core dumped)\n", 1);
		printf("%d\n", signo); //putnbr et \n
		display_prompt();
	}
	g_sig = 128 + signo;
}

void 	signal_handle(void)
{
	signal(SIGINT, signal_int);
	signal(SIGQUIT, signal_quit);
}
