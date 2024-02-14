NAME = minishell

CC = cc
FLAGS = -Wall -Wextra -Werror

LIBFT = ./libft/libft.a
LIBS = -L./libft -l:libft.a -lreadline
LIBFT_DIR = ./libft

INCLUDE = -I./includes

SD = src/
SRC = $(addprefix $(SD), minishell.c lexer.c lexer_utils.c list_handler.c \
						parser.c parser_utils.c moses_i.c moses_ii.c \
						hashtable.c expander.c path_finder.c finisher.c)
SRC += $(addprefix $(SD)builtin/, pwd.c)

TEST_SRC = $(addprefix $(SD), tests.c lexer.c lexer_utils.c list_handler.c \
						parser.c parser_utils.c moses_i.c moses_ii.c \
						hashtable.c expander.c path_finder.c finisher.c)
TEST_SRC += $(addprefix $(SD)builtin/, pwd.c env.c echo.c)

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
	$(CC) $(FLAGS) -gdwarf-4 $(TEST_SRC) $(LIBFT_DIR)/*.c $(LIBS) -o $(NAME)

.PHONY: all clean fclean re rebug frebug debug
