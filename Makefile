NAME 				= minishell
CC 					= cc #-fsanitize=address
CFLAGS 				= -Wall -Wextra -Werror -g

SRCS 				= main.c \
	   				signals/handle_signals.c \
					builtins/export_main.c \
					builtins/export_getsize.c \
					builtins/export_setnew.c \
					builtins/export_utils.c \
					builtins/export_substitutions.c \
					builtins/export_substitutions_utils.c \
					builtins/export_sub_lastsig.c \
					builtins/export_sub_lastsig_utils.c \
					builtins/export_identifier.c \
					builtins/export_identifier_utils.c \
					builtins/handle_errors.c \
					builtins/free_utils_export.c \
					builtins/modify_envp.c \
					builtins/modify_envp_utils.c \
					builtins/echo_main.c \
					builtins/echo_getsize.c \
					builtins/echo_setnew.c \
					builtins/unset_main.c \
					builtins/env_main.c \
					builtins/cd_main.c \
					builtins/cd_utils.c \
					builtins/pwd_main.c \
					builtins/exit_main.c \
					execute/execute_main_size.c \
					execute/execute_flags.c \
					execute/execute_heredocs.c \
					execute/execute_heredocs_utils.c \
					execute/execute_errors.c \
					execute/execute_free_utils.c \
					execute/execute_set_redirections.c \
					execute/execute_utils.c \
					execute/execute_transform_cmdlist.c \
					execute/execute_init_structs.c \
					execute/execute_redirect.c \
					execute/execute_dispatcher.c \
					execute/execute_onecommand.c \
					execute/execute_normalcmd.c \
					execute/execute_pathfinding.c \
					history/manage_history.c \
					history/manage_list.c \
					gnl/get_next_line.c \
					gnl/get_next_line_utils.c \
					parsing/parsing.c \
					parsing/manage_quotes.c \
					parsing/free_words.c \
					parsing/split_words.c \
					parsing/split_words1.c \
					parsing/init_structs.c \
					parsing/dollar_handler.c \
					parsing/lexer.c \
					parsing/count_delim.c \
					parsing/count_delim1.c \
					parsing/create_delim.c \
					parsing/check_builtins.c \
					parsing/fill_delim.c \

OBJS 				= $(SRCS:%.c=$(OBJ_D)%.o)

SRC_D 				= src/
OBJ_D 				= objects/

ifeq ($(shell uname), Darwin)
READLINEDIR 		= $(shell brew --prefix readline)
endif
INCLUDEDIR 			= includes
CFLAGS				+= -I$(READLINEDIR)/include
LIBREADLINE			= -lreadline -lhistory -L $(READLINEDIR)/lib
LIBFT				= -lft -L./libft

HEADERS 			= minishell.h \

all: libft
	@make --no-print-directory $(NAME)

$(OBJ_D)%.o: $(SRC_D)%.c $(INCLUDEDIR)/$(HEADERS)
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) -I./$(INCLUDEDIR) -c $< -o $@

$(NAME): $(OBJ_D) $(OBJS) Makefile includes/minishell.h libft/libft.a
	$(CC) $(CFLAGS) -I./$(INCLUDEDIR) $(OBJS) -o $(NAME) $(LIBFT) $(LIBREADLINE)

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

valgrind:       $(NAME)
	valgrind --track-fds=yes --trace-children=yes --leak-check=full --show-leak-kinds=all --suppressions=./ignore_leaks.supp ./$(NAME)

testexport:
	HEADERS="$(HEADERS) export_tests.h"
	@make SRCS="$(filter-out main.c, $(SRCS) tests/export_tests.c tests/get_next_line/get_next_line.c tests/get_next_line/get_next_line_utils.c tests/export_main_test.c)"

testexecute:
	HEADERS="$(HEADERS) execute.h get_next_line.h"
	@make SRCS="$(filter-out main.c, $(SRCS) tests/execute_tests.c)"

.PHONY: all clean fclean re libft testexport
