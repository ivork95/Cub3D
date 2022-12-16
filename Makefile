NAME :=		Cub3d
VPATH :=	src:\
			src/ft_strtol:\
			src/parse:\
			src/tokenize:\
			src/utils:\
			src/validate_tokens \
			src/graphics \
			src/init
HEADERS :=	includes/ft_strtol.h \
			includes/parse.h \
			includes/tokenize.h \
			includes/utils.h \
			includes/validate_tokens.h \
			includes/structs.h \
			includes/cub3d.h
MAIN :=		obj/main.o
OBJECTS :=	obj/ft_strtol_utils.o \
			obj/ft_strtol.o \
			obj/ll_to_a_map.o \
			obj/parse.o \
			obj/file_to_str.o \
			obj/tokenize.o \
			obj/prints.o \
			obj/utils.o \
			obj/floodfill.o \
			obj/validate_map_elements.o \
			obj/validate_non_map_elements.o \
			obj/render.o \
			obj/key_hook.o \
			obj/read_file.o \
			obj/init_cub.o \
			obj/textures.o
LDFLAGS ?=
CFLAGS ?=	-Wall -Wextra -Werror -g -I./includes/
LIBFT :=	./libft
MLX_DIR 	:= MLX42
MLX_LIB 	:= libmlx42.a
LINKS 		:= -lglfw3 -framework Cocoa -framework OpenGL -framework IOKit

all : libft $(NAME)

libft:
	make -C $(LIBFT)

$(NAME) : $(OBJECTS) $(MAIN)
	$(CC) -o $(NAME) $(MAIN) $(OBJECTS) $(LIBFT)/libft.a $(LDFLAGS) $(MLX_DIR)/$(MLX_LIB) $(LINKS)

$(OBJECTS) $(MAIN): obj/%.o : %.c
	@mkdir -p $(dir $@)
	$(CC) -c $(CFLAGS) -o $@ $<

clean :
	make clean -C $(LIBFT)
	rm -rf obj

fclean : clean
	make fclean -C $(LIBFT)
	rm -f $(NAME)

re : fclean all

.PHONY: all clean fclean re libft utests