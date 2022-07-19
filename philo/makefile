NAME = philo

SRC = main.c tools.c

OBJ = $(SRC:.c=.o)

CC = gcc

FLAGS = -Wall -Wextra -Werror
PTF = -lpthread

all : $(NAME)

$(NAME) : $(OBJ)
	$(CC) $(OBJ) $(FLAGS)  -o $(NAME)

%.o : %.c
	$(CC) $(FLAGS)  -c $<

clean :
	rm -rf $(OBJ)

fclean : clean
	rm -rf $(NAME)

re : fclean all