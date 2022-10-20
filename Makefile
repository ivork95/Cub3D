NAME =		Cube3D

SRCS =		src/main.c
INCLUDES =	-Ilibft -Iincludes -Imlx
OBJS =		$(SRCS:.c=.o)
LDFLAGS = 	-Lmlx -lmlx -framework OpenGL -framework AppKit
CFLAGS =	-Wall -Werror -Wextra
LIBFT	=	libft/libft.a

all: $(NAME)

$(NAME): $(OBJS) $(LIBFT) libmlx.dylib
	$(CC) $(INCLUDES) $(SRCS) $(LIBFT) $(LDFLAGS) mlx/libmlx.a -o $(NAME)

.c.o:
	$(CC) $(INCLUDES) -c $< -o $(<:.c=.o)

$(LIBFT):
	make -C libft

libmlx.dylib:
	make -C mlx

clean:
	rm -f $(OBJS)
	make -C libft clean

fclean:
	rm -f $(OBJS) $(NAME)
	make -C libft fclean
	make -C mlx clean

re: fclean all

.PHONY: all clean fclean re mlx libft bonus FORCE