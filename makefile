NAME = philo

SRC = main.c tools.c

OBJ = $(SRC:.c=.o)

CC = gcc

FLAGS = -Wall -Wextra -Werror
PTF = -lpthread

all : $(NAME)

$(NAME) : $(OBJ)
	$(CC) $(OBJ) $(FLAGS) $(PTF) -o $(NAME)

%.o : %.c
	$(CC) $(FLAGS) $(PTF) -c $<

clean :
	rm -rf $(OBJ)

fclean : clean
	rm -rf $(NAME)

re : fclean all