NAME = minishell

CC = cc
FLAGS = -Wall -Wextra -Werror

LIBFT = ./libft/libft.a
LIBS = -L./libft -l:libft.a -lreadline
LIBFT_DIR = ./libft

INCLUDE = -I./includes

SRC = $(addprefix src/, minishell.c lexer.c lexer_utils.c list_handler.c \
						variable_expander.c parser.c parser_utils.c moses.c \
						finisher.c hashtable.c)

OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(LIBFT) $(OBJ)
	$(CC) $(FLAGS) $(OBJ) $(INCLUDE) $(LIBS) -o $(NAME)

$(LIBFT):
	@make -C $(LIBFT_DIR) --no-print-directory

%.o:%.c
	$(CC) $(FLAGS) $(INCLUDE) -c $< -o $@

clean: 
	@make clean -C $(LIBFT_DIR) --no-print-directory
	rm -f $(OBJ)

fclean: clean
	rm -f $(LIBFT)
	rm -f $(NAME)

re: fclean $(NAME)

debug: $(LIBFT) $(OBJ)
	$(CC) $(FLAGS) -gdwarf-4 $(SRC) $(INCLUDE) $(LIBFT_DIR)/*.c $(LIBS) -o $(NAME)

rebug: clean debug

frebug: fclean debug

.PHONY: all clean fclean re rebug frebug debug
