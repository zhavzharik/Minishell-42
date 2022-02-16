#-fsanitize=address

NAME			= minishell

SRC_DIR			= srcs
OBJ_DIR			= objs

CC				= gcc
CFLAGS			= -Wall -Wextra -Werror -g

READLINE		= -lreadline -L/Users/$(USER)/.brew/Cellar/readline/8.1.1/lib/ -I/Users/$(USER)/.brew/Cellar/readline/8.1.1/include

LIB_DIR			= ./libft
LINK_LIBFT		= -Llibft -lft
LIB				= $(LIB_DIR)/libft.a

HDR				= includes/minishell.h
INCFLAGS		= -I./includes -I./libft

SRC				=	srcs/main.c \
					srcs/parser.c \
					srcs/quotes.c \
					srcs/dollar.c \
					srcs/redirects.c \
					srcs/tokens.c \
					srcs/signals.c \
					srcs/lsts.c \
					srcs/errors.c \
					srcs/utils.c \
                    srcs/ft_env_utils.c			\
                    srcs/ft_export.c			\
                    srcs/ft_export_utils.c		\
                    srcs/ft_clear.c				\
                    srcs/ft_data_utils.c		\
                    srcs/ft_errors.c			\
                    srcs/ft_action.c			\
                    srcs/action_utils.c			\
                    srcs/ft_cd_utils1.c			\
					srcs/ft_cd_utils2.c			\
                    srcs/ft_fd_redirect.c		\
					srcs/ft_fd_redirect_utils.c	\
					srcs/ft_fd_pipe.c			\
                    srcs/ft_echo_pwd.c			\
                    srcs/ft_cd.c				\
                    srcs/ft_unset.c				\
                    srcs/ft_exit.c				\
                    srcs/ft_env.c				\
                    srcs/ft_sorting.c			\
                    srcs/ft_libft_utils1.c		\
                    srcs/ft_libft_utils2.c

OBJ				= $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRC))

all				: $(NAME)

$(NAME)			: $(OBJ) $(LIB)
				@printf "objs		(created)\n"
				@$(CC) $(CFLAGS) $(OBJ) -L. libft/libft.a  $(READLINE) -o $@
				@printf "minishell	(created)\n"

$(OBJ_DIR)/%.o	: $(SRC_DIR)/%.c $(LIB) $(HDR)
				@mkdir -p $(OBJ_DIR)
				@$(CC) $(CFLAGS) -c $< -o $@

$(LIB)			:
				@make -C $(LIB_DIR)
				@printf "libft		(created)\n"

clean			:
				@$(MAKE) -C $(LIB_DIR) clean
				@rm -rf $(OBJ_DIR)
				@printf "objs		(del)\n"

fclean			: clean
				@$(MAKE) -C $(LIB_DIR) fclean
				@rm -f $(NAME)
				@printf "minishell	(del)\n"

re				: fclean all

.PHONY			: all clean fclean re
