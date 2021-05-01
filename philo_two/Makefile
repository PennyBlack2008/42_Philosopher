NAME	=	philo_two

SRCS	=	main.c \
			code_of_conduct.c \
			utils.c \
			waiter.c 

OBJS	=	$(SRCS:.c=.o)

CC		=	gcc

CFLAG	=	-Wall -Werror -Wextra 

RM		=	rm -rf

all		:	$(NAME)

clean	:	
			$(RM) $(OBJS)

fclean	:	clean
			$(RM) $(NAME) *.gch *.out .*.swp

re		:	fclean all

$(NAME)	:	$(OBJS)
			$(CC) $(CFLAG) -o $(NAME) $(OBJS)


