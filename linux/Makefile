# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: stakabay <stakabay@student.42tokyo.jp>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/04/03 02:04:56 by stakabay          #+#    #+#              #
#    Updated: 2021/04/03 19:14:05 by stakabay         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME := cub3D
CC := gcc -g
CFLAGS := -Wall -Wextra -Werror -I./
SRCNAME	= main.c \
			deal_key.c \
			deal_key2.c \
			main_loop.c \
			sprite.c \
			cast_ray.c \
			cast_ray2.c \
			./init/initialize.c \
			./init/init.c \
			./init/ft_malloc.c \
			./init/ft_compass.c \
			./init/ft_fcs.c \
			./init/read_elements.c \
			./init/player_pos.c \
			./init/mark.c \
			./init/mark2.c \
			./init/ft_atoi_cub.c \
			./init/ft_free.c \
			./init/read_image.c \
			./bmp/bitmap.c \

OBJS := $(SRCNAME:.c=.o)
LIBFT := libft.a
LIBFT_DIR := ./libft
LIBMLX := libmlx_Linux.a
LIBMLX_DIR := ./minilibx-linux
DYLIB := libmlx.dylib
DYLIB_DIR := ./minilibx_mms_20200219
GNL_DIR:= ./GNL
GNL := get_next_line.a
RM := rm -f

all:$(NAME)

ifeq ($(shell uname),Linux)
$(NAME):$(OBJS) $(LIBFT) $(LIBMLX) $(GNL)
	$(CC) $(CFLAGS) $^ -L. -lXext -lX11 -lm -o $@
clean:
	$(RM) $(OBJS)
	$(MAKE) clean -C $(LIBFT_DIR)
	$(MAKE) clean -C $(LIBMLX_DIR)
	$(MAKE) clean -C $(GNL_DIR)

fclean: clean
	$(RM) $(NAME) $(LIBFT) $(LIBMLX) $(GNL) 
	$(MAKE) fclean -C $(LIBFT_DIR)
	$(MAKE) fclean -C $(GNL_DIR)


else

$(NAME):$(OBJS) $(LIBFT) $(DYLIB) $(GNL)
	$(CC) $(CFLAGS) $^ -o $@ -framework OpenGL -framework AppKit

clean:
	$(RM) $(OBJS)
	$(MAKE) clean -C $(LIBFT_DIR)
	$(MAKE) clean -C $(GNL_DIR)
	$(MAKE) clean -C $(DYLIB_DIR)


fclean: clean
	$(RM) $(NAME) $(LIBFT) $(DYLIB) $(GNL)
	$(MAKE) fclean -C $(LIBFT_DIR)
	$(MAKE) fclean -C $(GNL_DIR)

endif
$(LIBFT):
	make -C $(LIBFT_DIR) && cp $(LIBFT_DIR)/$(LIBFT) .

$(LIBMLX):
	make -C $(LIBMLX_DIR) && cp $(LIBMLX_DIR)/$(LIBMLX) .

$(DYLIB):
	make -C $(DYLIB_DIR) && cp $(DYLIB_DIR)/$(DYLIB) .

$(GNL):
	make -C $(GNL_DIR) && cp $(GNL_DIR)/$(GNL) .

re:			fclean all

.PHONY:		clean fclean re all
