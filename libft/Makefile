NAME = libft.a

CC = cc
CFLAGS = -Wall -Wextra -Werror -c -O3
FLAGS = -Wall -Wextra -Werror -O3

SRC_FILES = ft_putchar_fd.c \
			ft_putstr_fd.c \
			ft_putendl_fd.c \
			ft_isalpha.c \
			ft_isdigit.c \
			ft_isalnum.c \
			ft_isascii.c \
			ft_isprint.c \
			ft_notspace.c \
			ft_strlen.c \
			ft_bzero.c \
			ft_memset.c \
			ft_memcpy.c \
			ft_memmove.c \
			ft_memcmp.c \
			ft_memchr.c \
			ft_tolower.c \
			ft_toupper.c \
			ft_strchr.c \
			ft_strrchr.c \
			ft_strcmp.c \
			ft_strncmp.c \
			ft_strnstr.c \
			ft_atoi.c \
			ft_atol.c \
			ft_atoll.c \
			ft_strlcpy.c \
			ft_strlcat.c \
			ft_strdup.c \
			ft_calloc.c \
			ft_substr.c \
			ft_strjoin.c \
			ft_strtrim.c \
			ft_split.c \
			ft_putnbr_fd.c \
			ft_striteri.c \
			ft_strmapi.c \
			ft_itoa.c \
			ft_lstnew_bonus.c \
		 	ft_lstadd_front_bonus.c \
		  	ft_lstsize_bonus.c \
		  	ft_lstlast_bonus.c \
		  	ft_lstadd_back_bonus.c \
		  	ft_lstdelone_bonus.c \
		  	ft_lstclear_bonus.c \
		  	ft_lstiter_bonus.c \
		  	ft_lstmap_bonus.c \
			get_next_line_bonus.c \
			get_next_line_utils_bonus.c \
			ft_printf.c \
			ft_printf_csint_utils.c \
			ft_printf_hex_utils.c \
			ft_printf_uint_utils.c \
			ft_printf_voidp_utils.c \
			ft_count_word.c


OBJ_FILES = $(SRC_FILES:.c=.o)
BONUS_OBJ_FILES = $(BONUS_FILES:.c=.o)

TEST_SRC = $(foreach file, $(SRC_FILES), test_$(file))
TEST_OBJ = $(TEST_SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ_FILES)

%.o : %.c
	@$(CC) $(CFLAGS) $< -o $@
	@ar -crs $(NAME) $@

clean:
	@rm -f *.o

fclean: clean
	rm -f $(NAME)

re: fclean $(NAME)

bonus: $(BONUS_OBJ_FILES)

test_%: $(NAME)
	$(CC) $(FLAGS) -L. -o ./tests/$@.out ./tests/$@.c -lbsd -l:$(NAME) -g3
	./tests/*.out

rmtests:
	rm -f *.out
