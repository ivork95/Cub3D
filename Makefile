NAME =		Cube3D

SRCS =		src/main.c
INCLUDES =	-Ilibft -Iincludes -Imlx_linux
OBJS =		$(SRCS:.c=.o)
CFLAGS =	-Wall -Werror -Wextra
LIBFT	=	libft/libft.a

all: $(NAME)

$(NAME): $(OBJS) $(LIBFT) libmlx.dylib
	$(CC) $(INCLUDES) $(SRCS) \
	$(LIBFT) mlx_linux/libmlx.a -lXext -lX11 -lm -lz -o $(NAME)

.c.o:
	$(CC) $(INCLUDES) -c $< -o $(<:.c=.o)

$(LIBFT):
	make -C libft

libmlx.dylib:
	make -C mlx_linux

clean:
	rm -f $(OBJS)
	make -C libft clean

fclean:
	rm -f $(OBJS) $(NAME)
	make -C libft fclean
	make -C mlx_linux clean

re: fclean all

.PHONY: all clean fclean re mlx libft bonus FORCE