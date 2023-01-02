NAME=philosopher
CC=gcc
HEADER=./include/
CFLAGS=-Wall -Werror -Wextra -I $(HEADER) -pthread
SRCS = activity.c \
	init.c \
	main.c \
	thread.c \
	utils1.c \
	utils2.c

OBJS=$(SRCS:.c=.o)

all:$(NAME)

$(NAME):$(OBJS) $(HEader)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

clean:
	rm -rf $(OBJS)
fclean: clean
	rm -rf $(NAME)
re: fclean all

.PHONY: all clean fclean re