SRCS	=	main.c\
			code_of_conduct.c\
			process_monitor.c\
			utils.c\
			waiter.c

OBJS	=	$(SRCS:.c=.o)

NAME	=	philo_three

CC		=	gcc

CFLAGS	=	-Wall -Wextra -Werror

RM		=	rm -rf

all		:	$(NAME)

clean	:
			$(RM) $(OBJS)

fclean	:	clean
			$(RM) $(NAME)

re		:	fclean all

$(NAME)	:	$(OBJS)
			$(CC) $(CFLAGS) -o $(NAME) $(OBJS)
