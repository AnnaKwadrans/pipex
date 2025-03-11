RM = rm -f
CC = cc
FLAGS = -Werror -Wextra -Wall -g
NAME = pipex
LIBFT_DIR = libft
LIBFT = libft/libft.a

SRC = main.c pipex_utils.c

OBJ = $(SRC:.c=.o)

%.o: %.c pipex.h
	$(CC) -I$(LIBFT_DIR) -c $< -o $@

$(NAME): $(OBJ)
	make -C libft
	$(CC) $(FLAGS) $(OBJ) -o $(NAME) -Llibft -lft

.PHONY:
	all re clean fclean

all: $(NAME)

clean:
	$(RM) $(OBJ)
	make clean -C libft

fclean: clean
	$(RM) $(NAME) $(LIBFT)

re: fclean all