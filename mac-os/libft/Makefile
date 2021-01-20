CC := gcc
CFLAGS := -Wall -Wextra -Werror -fPIC
LIBS := ar -rc
NAME := libft.a
SRCS := ft_atoi.c ft_bzero.c ft_calloc.c ft_isalnum.c ft_isalpha.c \
	ft_isascii.c ft_isdigit.c ft_isprint.c ft_itoa.c ft_memccpy.c \
	ft_memchr.c ft_memcmp.c ft_memcpy.c ft_memmove.c ft_memset.c \
	ft_putchar_fd.c ft_putendl_fd.c ft_putnbr_fd.c ft_putstr_fd.c \
	ft_split.c ft_strchr.c ft_strdup.c ft_strjoin.c ft_strlcat.c \
	ft_strlcpy.c ft_strlen.c ft_strmapi.c ft_strncmp.c ft_strnstr.c \
	ft_strrchr.c ft_strtrim.c ft_substr.c ft_tolower.c ft_toupper.c \

SONAME := libft.so
OBJS := $(SRCS:.c=.o)

so : $(NAME)
	${CC} ${CFLAGS} -shared ${OBJS} -o ${SONAME}

all: $(NAME)

$(NAME): $(OBJS)
	$(LIBS) $(NAME) $(OBJS)

clean:
	rm -f $(OBJS)
 
fclean: clean
	rm -f $(SONAME)
 
re: fclean all
 
.PHONY: all clean fclean re