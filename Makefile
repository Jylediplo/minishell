NAME 				= minishell
CC 					= cc
CFLAGS 				= -Wall -Wextra -Werror -g

SRCS 				= main.c \
	   				signals/handle_signals.c \
					builtins/specials.c \
					builtins/export.c \
					builtins/export_utils.c \
					builtins/handle_errors.c \

OBJS 				= $(SRCS:%.c=$(OBJ_D)%.o)

SRC_D 				= src/
OBJ_D 				= objects/

ifeq ($(shell uname), Darwin)
READLINEDIR 		= $(shell brew --prefix readline)
endif
INCLUDEDIR 			= includes
CFLAGS				+= -I$(READLINEDIR)/include
LIBTERMCAP			= -ltermcap
LIBREADLINE			= -lreadline -lhistory -L $(READLINEDIR)/lib
LIBFT				= -lft -L./libft

HEADERS 			= minishell.h

all: libft
	@make --no-print-directory $(NAME)

$(OBJ_D)%.o: $(SRC_D)%.c $(INCLUDEDIR)/minishell.h
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) -I./$(INCLUDEDIR) -c $< -o $@

$(NAME): $(OBJ_D) $(OBJS) Makefile includes/minishell.h libft/libft.a
	$(CC) $(CFLAGS) -I./$(INCLUDEDIR) $(OBJS) -o $(NAME) $(LIBFT) $(LIBREADLINE) $(LIBTERMCAP)

libft:	
	@make --no-print-directory -C libft

$(OBJ_D):
	@mkdir -p $(OBJ_D)

clean:
	@make clean -C libft
	rm -rf $(OBJ_D)

fclean: clean
	rm -f libft/libft.a
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re libft
