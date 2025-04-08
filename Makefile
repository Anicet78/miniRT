NAME = miniRT
SRCS = main.c
OBJDIR = obj
OBJS = $(patsubst %.c, $(OBJDIR)/%.o, $(SRCS))
CFLAGS = -Wall -Wextra -Werror
CC = clang
LIB = libft/libft.a
MLX_FOLDER = minilibx-linux

all: $(NAME)

$(MLX_FOLDER):
	git clone https://github.com/42Paris/minilibx-linux.git $(MLX_FOLDER)
	$(MAKE) -C $(MLX_FOLDER)

$(OBJDIR)/%.o: %.c | $(OBJDIR)
	$(CC) $(CFLAGS) -I/usr/include -Iminilibx-linux -g3 -c $< -o $@

$(OBJDIR):
	mkdir -p $(OBJDIR)

$(NAME): $(MLX_FOLDER) $(OBJS) $(LIB) 
	$(CC) $(CFLAGS) $(OBJS) $(LIB) -Lminilibx-linux -lmlx -L/usr/lib -Iminilibx-linux -lXext -lX11 -lm -lz -g3 -o $(NAME)

$(LIB):
	$(MAKE) -C libft

clean:
	rm -f $(OBJS)
	$(MAKE) clean -C libft

fclean: clean
	rm -f $(NAME)
	rm -rf $(MLX_FOLDER)
	rm -f $(LIB)

re: fclean all
		