NAME := cub3D
LIB := cub3D.a
CC := gcc
CFLAGS := -Wall -Wextra -Werror
AR := ar -rc
SRCS := cub.c ./readcub/readcubtxt.c sprite.c ./bmp/bitmap.c \
		./readcub/read_elements.c ./readcub/read_paths.c \
		./readcub/read_map.c ./readcub/read_playerpos.c sort_sprite.c \
		init.c deal_key.c cast_ray.c horver.c render.c projection.c

OBJS := $(SRCS:.c=.o)
LIBFT := libft.a
LIBFT_DIR := ./libft
LIBMLX := libmlx.a
LIBMLX_DIR := ./minilibx_opengl_20191021
LIBMLX_LI := libmlx_Linux.a
LIBMLX_LI_DIR := ./minilibx-linux
DYLIB := libmlx.dylib
DYLIB_DIR := ./minilibx_mms_20200219
GNL_DIR:= ./GNL
GNL := get_next_line.a

all: $(NAME)

ifeq ($(shell uname),Linux)
$(NAME):$(OBJS) $(LIBFT) $(LIBMLX)
	$(CC) $(CFLAGS) $^ -L. -lXext -lX11 -lm -o $@
clean:
	$(RM) $(OBJS) && make clean -C $(LIBFT_DIR) && make clean -C $(LIBMLX_DIR)

fclean: clean
	$(RM) $(NAME) $(LIBFT) $(LIBMLX) && make fclean -C $(LIBFT_DIR)

else

$(NAME): $(LIB) $(LIBFT) $(GNL) $(DYLIB) $(LIBMLX)
	$(CC) $(CFLAGS) -o $@ $(LIB) $(LIBMLX) $(LIBFT) $(GNL) $(DYLIB) -framework OpenGL -framework AppKit -g  -fsanitize=address

$(LIB): $(OBJS)
	$(AR) $(LIB) $(OBJS)

clean: 
	$(MAKE) clean -C $(LIBFT_DIR)
	$(MAKE) clean -C $(GNL_DIR)
	$(MAKE) clean -C $(DYLIB_DIR)
	$(MAKE) clean -C $(LIBMLX_DIR)
	$(RM) $(OBJS)

fclean: clean
	$(MAKE) fclean -C $(LIBFT_DIR)
	$(MAKE) fclean -C $(GNL_DIR)
	$(RM) $(NAME) $(LIBFT) $(DYLIB) $(GNL) $(LIBMLX) $(LIB)

endif
$(LIBFT):
	make -C $(LIBFT_DIR) && cp $(LIBFT_DIR)/$(LIBFT) .

$(LIBMLX):
	make -C $(LIBMLX_DIR) && cp $(LIBMLX_DIR)/$(LIBMLX) .

$(GNL):
	make -C $(GNL_DIR) && cp $(GNL_DIR)/$(GNL) .

$(LIBMLX_LI):
	make -C $(LIBMLX_LI_DIR) && cp $(LIBMLX_LI_DIR)/$(LIBMLX) .

$(DYLIB):
	make -C $(DYLIB_DIR) && cp $(DYLIB_DIR)/$(DYLIB) .

re: clean all
 
.PHONY: all clean fclean re