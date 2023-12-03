NAME = minishell

CC = cc
FLAGS = -Wall -Wextra -Werror

LIBFT = ./libft/libft.a
LIBS = -L./libft -l:libft.a -lreadline
LIBFT_DIR = ./libft

INCLUDE = ./includes

SRC = minishell.c

OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(LIBFT) $(OBJ)
	$(CC) $(FLAGS) $(SRC) -I$(INCLUDE) -o $(NAME) $(LIBS)

$(LIBFT):
	$(MAKE) -C $(LIBFT_DIR)

clean: 
	$(MAKE) -C $(LIBFT_DIR) clean
	rm -f *.o

fclean: clean
	rm $(LIBFT)
	rm -f $(NAME)

re: fclean $(NAME)

.PHONY: all clean fclean re
