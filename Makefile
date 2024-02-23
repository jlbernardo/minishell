NAME = minishell

CC = cc
FLAGS = -Wall -Wextra -Werror

LIBFT = ./libft/libft.a
LIBS = -L./libft -l:libft.a -lreadline
LIBFT_DIR = ./libft

INCLUDE = -I./includes

SD = src/
COMMON = $(addprefix $(SD), lexer.c lexer_utils.c list_handler.c \
						parser.c parser_utils.c create_pipeline.c moses_i.c \
						moses_ii.c hashtable.c expander.c path_finder.c \
						finisher.c executor.c exec_simple_command.c \
						exec_pipeline_commands.c \
						heredoc.c)
COMMON += $(addprefix $(SD)builtin/, pwd.c env.c echo.c cd.c exit.c \
						export.c export_utils.c unset.c)
SRC = $(COMMON) $(SD)minishell.c
TEST = $(COMMON) $(SD)test.c


OD = obj/
OBJ = $(SRC:$(SD)%.c=$(OD)%.o)

BLUE 	=	\033[1;36m
WHITE 	=	\033[0;39m
T_LIB	=	$(shell test -f ./libft/get_next_line_utils_bonus.o && echo "yes" 2>&1)

all: $(NAME)

$(NAME): $(LIBFT) $(OBJ)
	@echo "$(BLUE) Compiling...$(WHITE)"
	@$(CC) $(FLAGS) $(OBJ) $(INCLUDE) $(LIBS) -o $(NAME)
	@echo "$(BLUE) All done!$(WHITE)"

$(LIBFT):
	@if ! [ $(T_LIB) ]; then echo "$(BLUE) Creating libft library...$(WHITE)";fi
	@make -C $(LIBFT_DIR) --no-print-directory

$(OD)%.o:$(SD)%.c
	@mkdir -p $(dir $@)
	@$(CC) $(FLAGS) $(INCLUDE) -c $< -o $@

clean:
	@make clean -C $(LIBFT_DIR) --no-print-directory
	@rm -rf $(OD)
	@rm -f $(OBJ)
	@echo "$(BLUE) All objects were deleted.$(WHITE)"

fclean: clean
	@rm -f $(LIBFT)
	@rm -f $(NAME)
	@echo "$(BLUE) All binaries were deleted.$(WHITE)"

re: fclean $(NAME)

debug: $(LIBFT) $(OBJ)
	@echo "$(BLUE) Compiling...$(WHITE)"
	@$(CC) $(FLAGS) -gdwarf-4 $(SRC) $(INCLUDE) $(LIBFT_DIR)/*.c $(LIBS) -o $(NAME)
	@echo "$(BLUE) All done!$(WHITE)"

rebug: clean debug

frebug: fclean debug

test: clean $(LIBFT)
	@$(CC) $(FLAGS) -gdwarf-4 $(TEST) $(LIBFT_DIR)/*.c $(LIBS) -o $(NAME)

.PHONY: all clean fclean re rebug frebug debug
