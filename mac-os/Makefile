CC := gcc
CFLAGS := -Wall -Wextra -Werror
SRCS := cub.c ./readcub/readcubtxt.c sprite.c ./bmp/bitmap.c \
		./readcub/read_elements.c ./readcub/read_paths.c \
		./readcub/read_map.c ./readcub/read_playerpos.c sort_sprite.c \
		init.c deal_key.c cast_ray.c horver.c render.c projection.c
LIB := libmlx.a libmlx.dylib ./GNL/get_next_line.a ./libft/libft.a 

all:
	$(CC) $(CFLAGS) -I /usr/local/include $(SRCS) $(LIB) -framework OpenGL -framework AppKit -g  -fsanitize=address 

clean: clean
	rm -f $(NAME)
 
re: clean all
 
.PHONY: all clean fclean re