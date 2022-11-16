GREEN 		= \033[38;5;2m
NORMAL		= \033[38;5;255m
RED			= \033[38;5;1m
BLUE		= \033[38;5;4m
SRCS		=  	src/main.c\
				src/top_view.c\
				src/rays.c\
				src/key_hook.c\
				src/render.c
OBJS 		= $(SRCS:.c=.o)
LIBFT_DIR	= libft
LIBFT_LIB	= libft.a
NAME		= Cub3D
GCC			= gcc
FLAGS		= -Wall -Wextra -Werror -fsanitize=address -g
HEADER_FILE = cub3d.h
MLX_DIR 	= MLX42
MLX_LIB 	= libmlx42.a
LINKS 		= -lglfw3 -framework Cocoa -framework OpenGL -framework IOKit

all:    $(NAME)
$(NAME):	$(OBJS)
	$(MAKE) -C $(MLX_DIR)
	$(MAKE) -C $(LIBFT_DIR)
	$(GCC) $(FLAGS) -o $(NAME) $(OBJS) $(LIBFT_DIR)/$(LIBFT_LIB) $(MLX_DIR)/$(MLX_LIB) $(LINKS)
%.o: %.c $(HEADER_FILE)
	@echo "$(GREEN)Compiling:$(NORMAL)"
	$(GCC) $(FLAGS) -c $< -o $(<:.c=.o)
	@echo "$(GREEN)Successfully compiled!$(NORMAL)"
clean:
	@echo "$(RED)Removing all object files...$(NORMAL)"
	rm -f $(OBJS)
	make -C $(MLX_DIR) clean
	make -C $(LIBFT_DIR) clean
	@echo "$(GREEN)Succesfully removed all object files!$(NORMAL)"
fclean: clean
	@echo "$(RED)Removing libraries and bitmap file...$(NORMAL)"
	rm -f $(NAME)
	make -C $(MLX_DIR) clean
	make -C $(LIBFT_DIR) fclean
	@echo "$(GREEN)Successfully removed libraries and bitmap file!$(NORMAL)"
re: fclean all
.PHONY: clean fclean re