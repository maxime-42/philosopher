RM	= rm -f

CC = gcc -lpthread -g -Wall -Wextra -Werror -I  ./

NAME= philon_two

SRC	=	./main.c\
		./parser_arg.c\
		./libft.c\
		./cycle_philosopher.c\
		./utile.c\
		./init.c\
		./check_is_alive.c\

OBJ = $(SRC:.c=.o)

all	:$(NAME)

$(NAME)	:$(OBJ)
	$(CC) -o $(NAME) $(OBJ) 

clean	:
	rm -f $(NAME) $(OBJ)

fclean:	clean
	$(RM) $(NAME)

re	: clean all