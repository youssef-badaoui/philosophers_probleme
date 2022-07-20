NAME = philo_bonus

SRC = extra_bonus.c main_bonus.c tools_bonus.c

OBJ = $(SRC:.c=.o)

CC = gcc

FLAGS = -Wall -Wextra -Werror
PTF = -lpthread

all : $(NAME)

$(NAME) : $(OBJ)
	$(CC) $(OBJ) $(FLAGS)  -o $(NAME)

%.o : %.c
	$(CC) $(FLAGS)  -c $<

bonus : $(NAME)

clean :
	rm -rf $(OBJ)

fclean : clean
	rm -rf $(NAME)

re : fclean all