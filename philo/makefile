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

bonus : 
	@echo "bonus has his own MAKEFILE in ../philo/"

clean :
	rm -rf $(OBJ)

fclean : clean
	rm -rf $(NAME)

re : fclean all