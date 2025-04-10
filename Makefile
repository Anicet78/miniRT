CC			= cc
CFLAGS		= -ggdb#-Wall -Werror -Wextra

LIBFT_DIR	= libft
LIBFT		= $(LIBFT_DIR)/libft.a

INCLUDES	= includes/
SRC_DIR		= srcs/
OBJ_DIR		= objs/

CFLAGS		+= -I$(INCLUDES)

SRC			= main.c

OBJ			= $(patsubst %.c, $(OBJ_DIR)%.o, $(SRC))

NAME		= miniRT

all: $(NAME)

$(NAME): $(LIBFT) $(OBJ)
	@$(CC) $(CFLAGS) $(OBJ) $(LIBFT) -o $(NAME)
	@printf "                          \r\e[1;35mMiniRT Compiled\e[0m\n"

$(LIBFT):
	@make -sC $(LIBFT_DIR)

$(OBJ_DIR)%.o: $(SRC_DIR)%.c
	@mkdir -p $(dir $@)
	@printf "\e[1;35mCompiling %s\e[0m" $(notdir $<)
	@printf "                                            \r"
	@$(CC) $(CFLAGS) -c $< -o $@

clean:
	@printf "\e[1;36mCleaning files\e[0m\n"
	@rm -rf $(OBJ_DIR)
	@make clean -sC $(LIBFT_DIR)

fclean: clean
	@rm -rf $(NAME)
	@make fclean -sC $(LIBFT_DIR)

re: fclean all

.PHONY: all bonus clean fclean re
