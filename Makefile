# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: abridger <abridger@student.21-school.ru    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/01/05 18:35:44 by abridger          #+#    #+#              #
#    Updated: 2022/01/14 23:19:21 by abridger         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME			=	minishell

HEADER			=	minishell.h

SRCS			=	minishell.c		\
					ft_strlen.c		\
					ft_strcmp.c		\
					ft_str_utils.c	\
					ft_split.c		\
					ft_env_utils.c	\
					ft_clear.c		\
					ft_data_utils.c	\
					ft_errors.c		\
					ft_action.c		\
					ft_process.c	\
					ft_read_line.c



OBJS			=	$(SRCS:.c=.o)

CC				=	gcc

CFLAGS			=	-Wall -Wextra -Werror

LTFLAG			=	-ltermcap

LRFLAG			=	-lreadline

RM				=	rm -f

all:	$(NAME)

%.o: %.c $(HEADER) Makefile
	$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(LTFLAG) $(LRFLAG) $(OBJS) -o $@

clean:
		$(RM) $(OBJS)

fclean: clean
		$(RM) $(NAME)

re:	fclean all

.PHONY:	all clean fclean re
