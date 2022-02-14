#include "../includes/minishell.h"

t_info *add_new_info(void)
{
	t_info *tmp;

	tmp = (t_info *)malloc(sizeof(t_info));
	if (!tmp)
		return (NULL);
	tmp->token = 0;
	tmp->argc = 0;
	tmp->argv = NULL;
	tmp->output_file = NULL;
	tmp->fd_output_file = -2;
	tmp->input_file = NULL;
	tmp->fd_input_file = -2;
	tmp->heredoc = NULL;
	tmp->error = 0;
	tmp->nb_cmd = -1;
	tmp->fd_pipe[0] = -2;
	tmp->fd_pipe[1] = -2;
	tmp->pid = -2;
	tmp->head = tmp;
	tmp->prev = NULL;
	tmp->next = NULL;
	return (tmp);
}

void add_info(t_shell *msh)
{
	t_info	*new;
	t_info	*head;
	t_info	*temp;

	if (msh->info == NULL)
		msh->info = add_new_info();
	else
	{
		temp = msh->info;
		head = msh->info->head;
		new = add_new_info();
		msh->info->next = new;
		msh->info = msh->info->next;
		msh->info->prev = temp;
		msh->info->head = head;
	}
}

int minishell_parser(t_shell *msh, int *i)
{
	if (msh->str[*i] == '\'')
		return (single_quotes(msh, i));
	else if (msh->str[*i] == '\"')
		return (double_quotes(msh, i));
	else if (msh->str[*i] == '$')
		return (dollar(msh, i));
	else if (msh->str[*i] == ' ' || msh->str[*i] == '\t' || msh->str[*i] == 0)
		return (token_space(msh, i));
	else if (msh->str[*i] == '|')
		return (token_pipe(msh, i));
	else if (msh->str[*i] == '>')
	{
		if (msh->str[*i + 1] == '>')
			return(token_redirects(msh, i, TOKEN_REDIRECT_OUTPUT2));
		return (token_redirects(msh, i, TOKEN_REDIRECT_OUTPUT1));
	}
	else if (msh->str[*i] == '<')
	{
		if (msh->str[*i + 1] == '<')
			return(token_redirects(msh, i, TOKEN_HEREDOC));
		return (token_redirects(msh, i, TOKEN_REDIRECT_INPUT));
	}
	return (0);
}

int minishell_pre_parser(t_shell *msh)
{
	int i;
	char *new;

	i = 0;
	new = NULL;
	while (msh->str[i] == ' ' || msh->str[i] == '\t')
		i++;
	if (msh->str[i] == '|')
	{
		if (msh->str[i] == msh->str[i + 1])
			return (syntax_error(msh, msh->str + i, 2));
		return (syntax_error(msh, msh->str + i, 1));
	}
	if (!msh->str)
	{
		free(msh->str);
		return (1);
	}
	new = ft_strdup(msh->str + i);
	free(msh->str);
	msh->str = new;
	return (0);
}

int parser(t_shell *msh)
{
	int i;

	i = 0;
	if (minishell_pre_parser(msh))
		return (0);
	add_info(msh);
	while (msh->str)
	{
		if (minishell_parser(msh, &i))
			return (0);
		i++;
	}
	return (1);
}
