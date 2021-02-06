RM	= rm -f

CC = gcc -g -Wall -Wextra -Werror -I./

NAME= philon_one

SRC	=	./main.c\
		./parser_arg.c\
		./libft.c\

OBJ = $(SRC:.c=.o)

all	:$(NAME)

$(NAME)	:$(OBJ)
	$(CC) -o $(NAME) $(OBJ) 

clean	:
	rm -f $(NAME) $(OBJ)

fclean:	clean
	$(RM) $(NAME)

re	: clean all