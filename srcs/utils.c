#include "../includes/minishell.h"

void free_all(t_shell *msh)
{
	t_info *tmp;
	t_env *tmp2;
	int i;

	tmp2 = msh->env;
	while (tmp2)
	{
		tmp2->is_sorted = 0;
		tmp2->next_sorted = NULL;
		tmp2->first = NULL;
		tmp2 = tmp2->next;
	}
	if (msh->info != NULL)
		msh->info = msh->info->head;
	while (msh->info)
	{
		i = 0;
		while (msh->info->argv && msh->info->argv[i])
			free(msh->info->argv[i++]);
		free(msh->info->argv);
		if (msh->info->output_file)
			free(msh->info->output_file);
		if (msh->info->input_file)
			free(msh->info->input_file);
		if (msh->info->heredoc)
			free(msh->info->heredoc);
		tmp = msh->info;
		msh->info = msh->info->next;
		free(tmp);
	}
	while (msh->array && msh->array[i])
		free(msh->array[i++]);
	if (msh->str)
		free(msh->str);
	msh->have_a_pipe = 0; // это не используется?
	msh->check = 0;
}
