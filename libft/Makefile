NAME = libft.a
CFLAGS = -Wall -Werror -Wextra -I include
SRC = ft_isalpha.c \
      ft_toupper.c \
      ft_isalnum.c \
      ft_isascii.c \
      ft_isprint.c \
      ft_isdigit.c \
      ft_strncmp.c \
      ft_strchr.c \
      ft_memcpy.c \
      ft_memset.c \
      ft_strlcat.c \
      ft_calloc.c \
      ft_strlen.c \
      ft_strnstr.c \
      ft_strdup.c \
      ft_tolower.c \
      ft_bzero.c \
      ft_memchr.c \
      ft_strrchr.c \
      ft_memmove.c \
      ft_memcmp.c \
      ft_strlcpy.c \
      ft_atoi.c \
      ft_substr.c \
      ft_strjoin.c \
      ft_strtrim.c \
      ft_split.c \
      ft_itoa.c \
      ft_strmapi.c \
      ft_striteri.c \
      ft_putchar_fd.c \
      ft_putstr_fd.c \
      ft_putendl_fd.c \
      ft_putnbr_fd.c \
      ft_lstnew.c \
      ft_lstadd_front.c \
      ft_lstsize.c \
      ft_lstlast.c \
      ft_lstadd_back.c \
      ft_lstdelone.c \
      ft_lstclear.c \
      ft_lstiter.c \
      ft_lstmap.c

ifeq ($(shell uname), Darwin)
CC		= /opt/homebrew/opt/llvm/bin/clang -fsanitize=leak
endif

OBJS = $(SRC:.c=.o)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(OBJS)
	ar -rcs $(NAME) $(OBJS)

all: $(NAME)

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all bonus clean fclean re
