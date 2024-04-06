NAME = minishell

SRCS = main.c \
	   signals/handle_signals.c

OBJS = $(SRCS:%.c=$(OBJ_D)%.o)

SRC_D = src/
OBJ_D = objects/

CC = cc
CFLAGS = -Wall -Wextra -Werror
INCLUDEDIR = includes
HEADER = minishell.h

all:
	@make --no-print-directory $(NAME)

$(OBJ_D)%.o: $(SRC_D)%.c $(INCLUDEDIR)/minishell.h
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(OBJ_D) $(OBJS) Makefile includes/minishell.h
	$(CC) $(CFLAGS) $(OBJS) -lreadline -o $(NAME)

$(OBJ_D):
	@mkdir -p $(OBJ_D)

clean:
	rm -rf $(OBJ_D)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
