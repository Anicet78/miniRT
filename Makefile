CC			= cc
CFLAGS		= -ggdb #-Wall -Werror -Wextra

LIBFT_DIR	= libft
LIBFT		= $(LIBFT_DIR)/libft.a

MLX_DIR		= mlx
MLX			= $(MLX_DIR)/libmlx.a

INCLUDES	= includes/
SRC_DIR		= srcs/
OBJ_DIR		= objs/

CFLAGS		+= -I$(INCLUDES)

LIBS		= -Lmlx -lmlx -lXext -lX11 -lm

SRC			=	main.c							\
				elements/add_elements.c			\
				elements/add_elements2.c		\
				elements/add_xpm.c				\
				elements/elem_lst.c				\
				parse_file/check_params.c		\
				parse_file/libc_remaster.c		\
				parse_file/parse_elements.c		\
				parse_file/parse_elements2.c	\
				parse_file/parse_file.c			\
				parse_file/parse_xpm.c			\
				threads/queue.c					\
				threads/render.c				\
				threads/threads.c				\
				utils/err_message.c				\
				utils/color.c					\
				utils/print_tests.c				\
				utils/minmax.c					\
				utils/vec_utils.c				\
				raytraceur/closest_hit.c		\
				raytraceur/display.c			\
				raytraceur/hit_cylinder.c		\
				raytraceur/intersect.c			\
				raytraceur/print_utils.c		\
				raytraceur/vec3op.c				\
				raytraceur/vec3op2.c			\
				mlx.c

OBJ			= $(patsubst %.c, $(OBJ_DIR)%.o, $(SRC))

NAME		= miniRT

all: $(NAME)

$(NAME): $(LIBFT) $(MLX) $(OBJ)
	@$(CC) $(CFLAGS) $(OBJ) $(LIBFT) $(MLX) $(LIBS) -o $(NAME)
	@printf "                           \r\e[1;35mMiniRT Compiled\e[0m\n"

$(LIBFT):
	@make -sC $(LIBFT_DIR)

$(MLX):
	@printf "\r\e[1;31mCloning MinilibX\e[0m"
	@git clone https://github.com/42Paris/minilibx-linux.git $(MLX_DIR) 2>/dev/null
	@printf "\r\e[1;31mCompiling MinilibX\e[0m"
	@make -sC $(MLX_DIR) > /dev/null 2>&1
	@printf "\r\e[1;31mMinilibX Compiled\e[0m \b\n"

$(OBJ_DIR)%.o: $(SRC_DIR)%.c
	@mkdir -p $(dir $@)
	@printf "\e[1;35mCompiling %s\e[0m" $(notdir $<)
	@printf "                                            \r"
	@$(CC) $(CFLAGS) -c $< -o $@

bonus: $(NAME)

clean:
	@printf "\e[1;36mCleaning files\e[0m\n"
	@rm -rf $(OBJ_DIR)
	@make clean -sC $(LIBFT_DIR)

fclean: clean
	@rm -rf $(NAME)
	@rm -rf $(MLX_DIR)
	@make fclean -sC $(LIBFT_DIR)

re: fclean all

.PHONY: all bonus clean fclean re
