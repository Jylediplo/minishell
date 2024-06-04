NAME 				= minishell
CC 					= cc
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
					builtins/exit_utils.c \
					execute/execute_main_size.c \
					execute/execute_flags.c \
					execute/execute_flags_utils.c \
					execute/execute_heredocs.c \
					execute/execute_heredocs_utils.c \
					execute/execute_heredocs_termsettings.c \
					execute/execute_errors.c \
					execute/execute_free_utils.c \
					execute/execute_set_redirections.c \
					execute/execute_transform_cmdlist.c \
					execute/execute_init_structs.c \
					execute/execute_init_structs_utils.c \
					execute/execute_redirect.c \
					execute/execute_redirect_utils.c \
					execute/execute_dispatcher.c \
					execute/execute_dispatcher_utils.c \
					execute/execute_onecommand.c \
					execute/execute_normalcmd.c \
					execute/execute_normalcmd_utils.c \
					execute/execute_pathfinding.c \
					execute/execute_error_pipes.c \
					execute/execute_error_pipes_utils.c \
					execute/execute_wait_and_readerrors.c \
					execute/execute_modify_io.c \
					history/manage_history.c \
					history/manage_list.c \
					gnl/get_next_line.c \
					gnl/get_next_line_utils.c \
					parsing/parsing.c \
					parsing/manage_quotes.c \
					parsing/manage_quotes_utils.c \
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
CC					= /usr/bin/clang #-fsanitize=leak
endif

INCLUDEDIR 			= includes
CFLAGS				+= -I$(READLINEDIR)/include
LIBREADLINE			= -lreadline -lhistory -L $(READLINEDIR)/lib
LIBFT				= -lft -L./libft

HEADERS 			= $(INCLUDEDIR)/minishell.h \
					  $(INCLUDEDIR)/evars.h \
					  $(INCLUDEDIR)/execute.h \
					  $(INCLUDEDIR)/get_next_line.h \
					  $(INCLUDEDIR)/lexing.h \

all: libft
	@make --no-print-directory $(NAME)

$(OBJ_D)%.o: $(SRC_D)%.c $(HEADERS)
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) -I./$(INCLUDEDIR) -c $< -o $@

$(NAME): $(OBJ_D) $(OBJS) Makefile $(HEADERS) libft/libft.a
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

.PHONY: all clean fclean re libft
