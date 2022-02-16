/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abridger <abridger@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/14 17:51:03 by pkari             #+#    #+#             */
/*   Updated: 2022/02/16 14:33:33 by abridger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <fcntl.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <signal.h>
# include <errno.h>
# include "../libft/libft.h"

# define TOKEN_PIPE				1 // |
# define TOKEN_REDIRECT_INPUT	2 // < (fd 0)
# define TOKEN_REDIRECT_OUTPUT1	3 // > (fd 1) перезаписывает файл
# define TOKEN_REDIRECT_OUTPUT2	4 // >> (fd 1) дописывает в файл
# define TOKEN_HEREDOC			5 // << 'EOF' пока не встретит EOF читает из out

typedef struct s_env
{
	char			*key;
	char			*sep;
	char			*value;
	int				is_sorted;
	struct s_env	*prev;
	struct s_env	*next;
	struct s_env	*first;
	struct s_env	*next_sorted;
}					t_env;

typedef struct s_info
{
	int				token;
	int				is_pipe;
	int				redirect_flag;
	int				argc;
	char			**argv;
	char			*output_file;
	int				fd_output_file;
	char			*input_file;
	int				fd_input_file;
	char			*heredoc_file;
	char			*heredoc;
	int				fd_heredoc_file;
	int				error;
	int				nb_cmd;
	int				fd_pipe[2];
	int				pid;
	struct s_info	*head;
	struct s_info	*prev;
	struct s_info	*next;
}					t_info;

typedef struct s_shell
{
	t_info	*info;
	t_env	*env;
	char	*str;
	char	**array;
	int		exit_status;
	int		have_a_pipe;
	int		save_in;
	int		save_out;
	int		count;
	int		check;
	char	*home_value;
	int		flag_path;
}			t_shell;

typedef int	(*t_builtin)(t_shell *, t_info *);

//**************************//
//**********PKARI***********//
//**************************//

//*** main.c ***//
void		init_shell(t_shell *msh);
void		create_env(t_shell *msh, char **env);
char		*get_dollar_env(t_env *env, char *str);
void		shlvl(t_shell *msh);

//*** parser.c ***//
int			parser(t_shell *msh);
int			minishell_pre_parser(t_shell *msh);
int			minishell_parser(t_shell *msh, int *i);
void		add_info(t_shell *msh);
t_info		*add_new_info(void);

//*** quotes.c ***//
int			single_quotes(t_shell *msh, int *i);
int			double_quotes(t_shell *msh, int *i);

//*** dollar.c ***//
int			dollar(t_shell *msh, int *i);
int			dollar_env(t_shell *msh, int *i, int j);
int			dollar_pass(t_shell *msh, int *i, int j);
int			dollar_ignore(t_shell *msh, int *i, int j);
int			dollar_question(t_shell *msh, int *i, int j);

//*** tokens.c ***//
int			token_space(t_shell *msh, int *i);
int			token_pipe(t_shell *msh, int *i);
int			token_redirects(t_shell *msh, int *i, int token);
void		token_handler(t_shell *msh, int *i);

//*** redirects.c ***//
void		redirect_input(t_shell *msh, int *i);
void		redirect_output(t_shell *msh, int *i);
void		redirect_heredoc(t_shell *msh, int *i);

//*** signals.c ***//
void		ctrl_c(int signal);
void		ctrl_d(void);
void		ctrl_c2(int signal);

//*** lsts.c ***//
void		msh_lstadd_back(t_env **env, t_env *new);
t_env		*msh_lstlast(t_env *env);
t_env		*msh_lstnew(char *ket, char *val);
int			msh_lstsize(t_info *curr);

//*** errors.c ***//
int			syntax_error(t_shell *msh, char *str, int len);
void		errno_error(t_shell *msh);
void		execve_error(t_shell *data);

//*** utils.c ***//
void		dollar_env2(t_shell *msh, char *tmp);
void		free_all(t_shell *msh);
void		rl_replace_line(const char *text, int clear_undo);

//*** action_utils.c ***//
char		*get_prog_name(t_shell *data, t_info *curr);
char		**get_arr_from_lst(t_shell *data);
void		exit_status_handler(t_shell *data);

//**************************//
//*********ABRIDGER*********//
//**************************//

//*** ft_data_utils.c ***//
int			ft_len_key(char *str);
int			ft_len_value(char *str);
int			ft_height_array(char **array);

//*** ft_env_utils.c ***//
void		ft_add_ptr(t_env **new);
t_env		*ft_lstnew(const char *line);
t_env		*ft_lstlast(t_env *lst);
void		ft_lstadd_back(t_env **lst, t_env *new);
t_env		*parse_envrmnt(t_env *lst, char **envp);

//*** ft_sorting.c ***//
t_env		*ft_find_first(t_shell *data);
int			ft_unsorted(t_shell *data);
t_env		*ft_find_next(t_shell *data);
t_env		*ft_find_last(t_shell *data);
t_env		*ft_sort_env(t_shell *data);

//*** ft_action.c ***//
int			action(t_shell *data);
void		ft_define_cmd(t_shell *data);
int			ft_simple_execute(t_shell *data, t_info *curr, t_builtin *func);
int			ft_execute(t_shell *data, t_info *curr, t_builtin *func);
void		ft_execution_cycle(t_shell *data);

//*** ft_fd_redirect.c ***//
void		ft_init_saved_fd(t_shell *data);
void		ft_close_saved_fd(t_shell *data);
void		ft_redirect_dup(t_info *curr);
void		ft_close_curr_files(t_info *curr);

//*** ft_fd_redirect_utils.c ***//
void		ft_redirect_output(t_info *curr);
void		ft_redirect_input(t_info *curr);
void		ft_read_input(t_info *curr);

//*** ft_fd_pipe.c ***//
int			ft_pipe_init(t_shell *data, t_info *curr);
void		ft_pipe_close(t_shell *data, t_info *curr);
void		ft_pipe_dup_child(t_shell *data, t_info *curr);
void		ft_pipe_dup_parent(t_shell *data, t_info *curr);

//*** ft_exit.c ***//
int			ft_right_digit(char *str);
int			ft_err_exit(t_shell *data, char *str, int flag);
int			ft_right_exit(t_shell *data, t_info *curr, int flag);
int			ft_exec_exit(t_shell *data, t_info *curr);

//*** ft_env.c ***//
int			ft_wrong_path(t_shell *data);
int			ft_err_env_args(t_shell *data, char *str);
int			ft_exec_env(t_shell *data, t_info *curr);

//*** ft_echo_pwd.c ***//
t_builtin	*create_array_function(void);
void		print_argv(char **str, int indx);
int			ft_exec_echo(t_shell *data, t_info *curr);
int			ft_exec_pwd(t_shell *data, t_info *curr);

//*** ft_cd.c ***//
void		ft_add_oldpwd_env(t_shell *data, char *curr_pwd);
void		ft_change_oldpwd_env(t_shell *data, char *curr_pwd, int check);
void		ft_change_pwd_env(t_shell *data, char *curr_pwd, char *new_pwd);
int			ft_err_many_args(t_shell *data);
int			ft_exec_cd(t_shell *data, t_info *curr);

//*** ft_cd_utils1.c ***//
int			ft_err_no_dir(t_shell *data, char *str);
void		ft_get_home(t_shell *data);
int			ft_add_home_dir(t_shell *data, char *line, char *curr_pwd);
int			ft_check_args(t_shell *data, t_info *curr, char *curr_pwd);

//*** ft_cd_utils2.c ***//
int			ft_no_oldpwd(t_shell *data, char *str);
void		ft_write_str(char *str);
int			ft_print_dir(t_shell *data, char *curr_pwd);
int			ft_err_option(t_shell *data, char *str);

//*** ft_unset.c ***//
int			ft_err_unset(t_shell *data, char *str);
void		ft_del_lst(char *str, t_env *env, t_shell *data);
void		ft_del_lst_support(t_env *env, t_shell *data);
int			ft_exec_unset(t_shell *data, t_info *curr);

//*** ft_export.c ***//
int			ft_env_check(const char *line, t_env *tmp);
void		ft_lst_change_value(t_env *lst, const char *line);
void		ft_add_variable(t_info *curr, t_shell *data);
void		ft_print_export(t_shell *data, int height);
int			ft_exec_export(t_shell *data, t_info *curr);

//*** ft_export_utils.c ***//
int			ft_check_char(int c);
int			ft_check_key(char *str);
int			ft_err_export(t_shell *data, char *str);

//*** ft_errors.c ***//
int			put_err_message(char *str);
int			ft_error(t_shell *data, char *str);
char		*ft_two_colon(char *s1, char *s2);
char		*ft_one_colon(char *s1);

//*** ft_clear.c ***//
void		ft_env_clear(t_env **lst);
void		ft_data_clear(t_shell *data);
void		ft_str_clear(char **str);

//*** ft_libft_utils.c ***//
int			ft_strcmp2(const char *s1, const char *s2);
void		*ft_memcpy2(void *dst, const void *src, size_t n);
char		*ft_strjoin2(char const *s1, char const *s2);
char		*ft_strnstr2(const char *haystack, const char *needle, size_t len);
char		**ft_split2(char const *s, char c);

#endif
