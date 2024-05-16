NAME := minishell
CC := cc
CFLAGS := -Wextra -Wall -Werror -g
LIBFT := libft/libft.a
HEADER := -I ./header
SRC_DIR := ./src
OBJ_DIR := ./obj

# Recursive wildcard function to find all .c files in subdirectories
#rwildcard=$(wildcard $1$2) $(foreach d,$(wildcard $1*),$(call rwildcard,$d/,$2))

# SRCS := $(call rwildcard,$(SRC_DIR)/,*.c)
SRCS := ./src/buildins/cd.c\
./src/buildins/cd2.c\
./src/buildins/cd_update_pwd.c\
./src/buildins/dollar.c\
./src/buildins/dollar_util.c\
./src/buildins/dollar_util2.c\
./src/buildins/echo.c\
./src/buildins/env.c\
./src/buildins/exit.c\
./src/buildins/export.c\
./src/buildins/export2.c\
./src/buildins/export3.c\
./src/buildins/handle_buildin_call.c\
./src/buildins/pwd.c\
./src/buildins/unset.c\
./src/env/env_handling.c\
./src/env/env_utils.c\
./src/env/export_list.c\
./src/env/lst.c\
./src/get_next_line/get_next_line.c\
./src/get_next_line/get_next_line_utils.c\
./src/get_next_line/helper.c\
./src/lexer/constructor.c\
./src/lexer/do_exec.c\
./src/lexer/do_exec_parent.c\
./src/lexer/do_pipe.c\
./src/lexer/free.c\
./src/lexer/free2.c\
./src/lexer/here_doc.c\
./src/lexer/main.c\
./src/lexer/minishell.c\
./src/lexer/my_functions.c\
./src/lexer/my_functions_in_parent.c\
./src/lexer/parse_util.c\
./src/lexer/parser.c\
./src/lexer/parser_util2.c\
./src/lexer/parser_util3.c\
./src/lexer/path_action.c\
./src/lexer/prompt.c\
./src/lexer/quotes.c\
./src/lexer/quotes_helper.c\
./src/lexer/quotes_helper2.c\
./src/lexer/redir.c\
./src/lexer/redir_pars.c\
./src/lexer/run_utils.c\
./src/lexer/runcmd.c\
./src/lexer/write_argv.c\
./src/lexer/write_argv_util.c\
./src/signals/ctrl.c\
./src/signals/init_sig_in_child.c


OBJS := $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRCS))
OBJ_DIRS := $(sort $(dir $(OBJS)))

all: $(NAME)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIRS)
	$(CC) $(CFLAGS) $< -c -o $@ $(HEADER)

$(NAME): $(OBJS)
	make -C libft
	$(CC) $(CFLAGS) $(OBJS) -I include $(LIBFT) -g -o $(NAME) -lreadline $(HEADER)

$(OBJ_DIRS):
	mkdir -p $@

clean:
	make clean -C libft
	rm -rf $(OBJ_DIR)

fclean: clean
	make fclean -C libft
	rm -f $(NAME)



re: clean all

.PHONY: all clean fclean re
