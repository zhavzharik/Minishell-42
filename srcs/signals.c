#include "../includes/minishell.h"

void ctrl_c(int signal)
{
	(void)signal;
	rl_on_new_line();
	rl_redisplay();
	write(2, "   \n", 4);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
	return ;
}

void ctrl_d(void)
{
	write(1, "exit\n", 5);
	rl_redisplay();
	exit(0);
}

void ctrl_c2(int signal)
{
	(void)signal;
	write(2, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	return ;
}

