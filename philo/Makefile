NAME = philo
CC = gcc
CFLAGS = -Wall -Wextra -Werror -g -fsanitize=thread

SRCS = main.c control.c utils.c inits.c sim.c destroy.c display.c stalker.c

OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	@$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

clean:
	@rm -f $(OBJS)

fclean: clean
	@rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
