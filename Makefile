NAME = 		cub3d
SRCS_DIR = 	srcs
OBJS_DIR = 	.objs
LIBFT_DIR = libft
LIBFT = 	$(LIBFT_DIR)/libft.a
MLX_DIR = 	minilibx-linux
MLX = 		$(MLX_DIR)/libmlx.a
SRCS = 		$(SRCS_DIR)/main.c \
				$(SRCS_DIR)/player_movements.c \
				$(SRCS_DIR)/shapes.c \
				$(SRCS_DIR)/rays.c \
				$(SRCS_DIR)/map.c \
				$(SRCS_DIR)/map_reader.c \
				$(SRCS_DIR)/aux_functions.c 

OBJS = $(patsubst $(SRCS_DIR)%.c,  $(OBJS_DIR)%.o,  $(SRCS))

CC = 		clang
HEAD = 		-I./include -I./$(LIBFT_DIR) -I./$(MLX_DIR)

LFLAGS =	-lbsd -lm -lX11 -lXext \
			-L ./$(LIBFT_DIR) -lft \
			-L ./$(MLX_DIR) -lmlx
RM = 		/bin/rm -rf

all: $(NAME)

$(NAME): $(OBJS) $(LIBFT) $(MLX)
	$(CC) $(OBJS) $(HEAD) $(LFLAGS) -o $@

$(OBJS_DIR)/%.o: $(SRCS_DIR)/%.c
	mkdir -p $(OBJS_DIR)
	$(CC) $(HEAD) -c $< -o $@

$(MLX):
	make -C $(MLX_DIR)

$(LIBFT):
	make -C $(LIBFT_DIR)

clean:
	make clean -C $(MLX_DIR)
	make clean -C $(LIBFT_DIR)
	$(RM) $(OBJS_DIR)

fclean: clean
	make fclean -C $(LIBFT_DIR)
	$(RM) $(NAME)
	$(RM) *.bmp

re: fclean all

.PONY: all clean fclean re
