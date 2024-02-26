NAME = minishell

CC = cc
FLAGS = -Wall -Wextra -Werror

LIBFT = ./libft/libft.a
LIBS = -L./libft -l:libft.a -lreadline
LIBFT_DIR = ./libft

INCLUDE = -I./includes

SD = src/
COMMON += $(addprefix $(SD)executor/, executor.c executor_utils.c pipeline.c \
						exec_simple_command.c exec_pipeline_commands.c)
COMMON += $(addprefix $(SD)lexer/, lexer.c lexer_utils.c)
COMMON += $(addprefix $(SD)parser/, parser.c expander.c path_finder.c)
COMMON += $(addprefix $(SD)utils/, list_handler.c moses_i.c moses_ii.c \
						hashtable.c finisher.c conditionals.c set_structures.c \
						error_handler.c sig_handler.c)
COMMON += $(addprefix $(SD)builtins/, pwd.c env.c echo.c cd.c exit.c \
						export.c export_utils.c unset.c)
COMMON += $(addprefix $(SD)redirect/, heredoc.c)

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
