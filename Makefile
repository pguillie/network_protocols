NAME	= netp

CC	= gcc
CFLAGS	= -Wall -Werror -Wextra

sources	= main.c send_udp.c
objects	= $(sources:.c=.o)

all: $(NAME)

$(NAME): $(objects)
	$(CC) -o $(NAME) $(objects)

clean:
	$(RM) $(objects)

cap:
	setcap cap_net_raw=pe $(NAME)
