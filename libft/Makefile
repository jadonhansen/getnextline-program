NAME = libft.a
OBJECTS = *.o
SRC = *.c
FLAGS = -Wall -Werror -Wextra
OPTIONS = -c -I.

all: $(NAME)

$(NAME): 
	gcc $(FLAGS) $(SRC) $(OPTIONS)
	ar rc $(NAME) $(OBJECTS)
	ranlib $(NAME)

clean: 
	/bin/rm -f $(OBJECTS)

fclean: clean
	/bin/rm -f $(NAME)

re: fclean all
