#include "../includes/minishell.h"

void shlvl(t_shell *msh)
{
	t_env *tmp;
	int shlvl;

	tmp = msh->env;
	while (1)
	{
		if (!tmp)
		{
			msh_lstadd_back(&tmp, msh_lstnew(ft_strdup("SHLVL"),ft_strdup
			("1")));
			break ;
		}
		else if (!(ft_strcmp("SHLVL", tmp->key)))
		{
			shlvl = ft_atoi(tmp->value);
			if (tmp->value != NULL)
				free(tmp->value);
			if (shlvl < 0)
				tmp->value = ft_strdup("1");
			else
				tmp->value = ft_itoa(shlvl + 1);
			break ;
		}
		tmp = tmp->next;
	}
}

char *get_dollar_env(t_env *env, char *str)
{
	t_env *tmp;

	tmp = env;
	while (tmp)
	{
		if (!ft_strcmp(str, tmp->key))
			return (tmp->value);
		tmp = tmp->next;
	}
	return ("");
}

void create_env(t_shell *msh, char **env)
{
	char **tmp;
	int i;

	i = 0;
	while (env[i])
	{
		tmp = ft_split(env[i], '=');
		msh_lstadd_back(&msh->env, msh_lstnew(tmp[0], tmp[1]));
		free(tmp);
		i++;
	}
}

void init_shell(t_shell *msh)
{
	msh->env = NULL;
	msh->array = NULL;
	msh->info = NULL;
	msh->exit_status = 0;
	msh->have_a_pipe = 0;
	msh->check = 0;
}

int main(int argc, char **argv, char **env)
{
	t_shell msh;

	(void)argv;
	if (argc != 1)
	{
		write(1, "Error: wrong number of arguments\n", 33);
		return (1);
	}
	init_shell(&msh);
	msh.env = parse_envrmnt(msh.env, env);
//	create_env(&msh, env);
	shlvl(&msh);
	while (1)
	{
		signal(SIGINT, ctrl_c);
		signal(SIGQUIT, SIG_IGN);
		msh.str = readline("\x1b[32mminishell$\x1b[0m ");
		if (msh.str == NULL)
			ctrl_d();
		add_history(msh.str);
		if (parser(&msh)) // parser part (pkari)
			action(&msh); // builtin part (abridger)
		free_all(&msh);
	}
	free_all(&msh);
	ft_data_clear(&msh);
}

