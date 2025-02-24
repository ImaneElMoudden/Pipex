CC = cc
CFLAGS = -Wall -Wextra -Werror
SRC = pipex.c pipex_helper.c fork_f.c libft_helper.c ft_split.c
OBJ = $(SRC:.c=.o)
NAME = pipex

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME)

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re