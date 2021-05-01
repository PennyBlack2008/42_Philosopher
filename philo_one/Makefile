SRCS	=	main.c \
			philo_act.c \
			utils.c \
			waiter.c

OBJS	=	$(SRCS:.c=.o)

NAME	=	philo_one
RM		=	rm -rf
CC		=	gcc
CFLAG	=	-Wall -Werror -Wextra

all		:	$(NAME)

clean	:
			$(RM) $(OBJS) *.gch .*.swp *.out

fclean	:	clean
			$(RM) $(NAME)

re		:	fclean all

$(NAME)	:	$(OBJS)
			$(CC) $(CFLAG) -o $(NAME) $(OBJS)
