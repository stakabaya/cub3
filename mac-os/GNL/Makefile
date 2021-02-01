NAME := get_next_line.a
CC := gcc
CFLAGS := -Wall -Wextra -Werror
AR := ar rc
SRCS := get_next_line.c get_next_line_utils.c
OBJS := $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(AR) $@ $^

clean: 
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)
 
re: clean all
 
.PHONY: all clean fclean re