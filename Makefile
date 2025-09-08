CC			= cc
CFLAGS		= -Wall -Werror -Wextra -ggdb
DEBUGFLAGS	= -ggdb #-fsanitize=address,undefined,leak
FASTFLAGS	= -Ofast -flto -ffast-math -march=native -pipe

LIBFT_DIR	= libft
LIBFT		= $(LIBFT_DIR)/libft.a

MLX_DIR		= mlx
MLX			= $(MLX_DIR)/libmlx.a

INCLUDES	= -Iincludes/common -Iincludes/full
SRC_DIR		= srcs/
OBJ_DIR		= objs/

CFLAGS		+= -I$(INCLUDES)

MODE ?= normal

ifeq ($(MODE), fast)
	CFLAGS += $(FASTFLAGS)
endif
ifeq ($(MODE), debug)
	CFLAGS += $(DEBUGFLAGS)
endif

LIBS		= -Lmlx -lmlx -lXext -lX11 -lm

SRC			=	main.c							\
				bvh/aabb.c						\
				bvh/bins.c						\
				bvh/bvh.c						\
				bvh/hit_bvh.c					\
				bvh/indexs.c					\
				bvh/utils.c						\
				bvh/utils2.c					\
				elements/add_elements.c			\
				elements/add_elements2.c		\
				elements/add_xpm.c				\
				elements/elem_lst.c				\
				parse_file/alloc_elems.c		\
				parse_file/check_params.c		\
				parse_file/init_parsing.c		\
				parse_file/libc_remaster.c		\
				parse_file/parse_elements.c		\
				parse_file/parse_elements2.c	\
				parse_file/parse_file.c			\
				parse_file/parse_xpm.c			\
				ray/closest_hit.c				\
				ray/display.c					\
				ray/hit_aabb.c					\
				ray/hit_cone.c					\
				ray/hit_cyl.c					\
				ray/hits.c						\
				ray/phong.c						\
				ray/texture.c					\
				ray/vec3op.c					\
				ray/vec3op2.c					\
				ray/vec3op3.c					\
				threads/queue.c					\
				threads/render.c				\
				threads/threads.c				\
				utils/calc_things.c				\
				utils/color.c					\
				utils/err_message.c				\
				utils/fps.c						\
				utils/mlx_end.c					\
				utils/mlx_hook.c				\
				utils/mlx.c						\
				utils/print_utils.c				\
				utils/time.c					\
				utils/vec_utils.c

OBJ			= $(patsubst %.c, $(OBJ_DIR)%.o, $(SRC))

NAME		= miniRT

all: $(NAME)

$(NAME): $(LIBFT) $(MLX) $(OBJ)
	@$(CC) $(CFLAGS) $(OBJ) $(LIBFT) $(MLX) $(LIBS) -o $(NAME)
	@printf "\r\e[2K\e[1;35mMiniRT Compiled\e[0m\n"

$(LIBFT):
	@make -sC $(LIBFT_DIR)

$(MLX):
	@printf "\r\e[1;31mCloning MinilibX\e[0m"
	@git clone https://github.com/42Paris/minilibx-linux.git $(MLX_DIR) 2>/dev/null
	@printf "\r\e[1;31mCompiling MinilibX\e[0m"
	@make -sC $(MLX_DIR) > /dev/null 2>&1
	@printf "\r\e[1;31mMinilibX Compiled\e[0m \b\n"

INDEX=0
TOTAL=$(words $(SRC))

$(OBJ_DIR)%.o: $(SRC_DIR)%.c
	@mkdir -p $(dir $@)
	$(eval INDEX=$(shell echo $$(($(INDEX)+1))))
	@printf "\r\e[2K\e[1;35mCompiling [%d/%d] %s\e[0m" $(INDEX) $(TOTAL) $(notdir $<)
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
