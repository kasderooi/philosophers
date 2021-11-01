NAME	=	philo

SRCS	=	philo.c lib_utils.c action_utils.c actions.c init.c

OBJS	=	$(SRCS:.c=.o)

CC		=	gcc
CFLAGS	=	-Wall -Wextra -Werror
INC		=	minishell.h

LIBS 	=	-lpthread

all: $(NAME)

$(NAME): $(OBJS)
	@echo "\n"
	@$(CC) $(CFLAGS) -o $(NAME) $(OBJS) $(LIBS)
	@echo "You can now run ./philo, enjoy!"

%.o: %.c
	@printf "Building philo objects... %-33.33s\r" $@
	@$(CC) $(CFLAGS) -c $< -o $@

clean:
		@rm -f $(OBJS)

fclean: clean
		@rm -f $(NAME)

re: fclean all
