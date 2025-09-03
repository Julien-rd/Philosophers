NAME = philo

CC = cc
CFLAGS = -Wall -Wextra -Werror -g -I. -Iprintf

SRCDIR = .
UTILDIR = utils

SOURCES = $(SRCDIR)/main.c \
          $(UTILDIR)/ft_atoi.c \
          $(UTILDIR)/initialise_data.c \
          $(UTILDIR)/gettime.c \
          $(UTILDIR)/initialise_philos.c \
          $(UTILDIR)/actions.c \
          $(UTILDIR)/routine.c 

OBJECTS = $(SOURCES:.c=.o)

all: $(NAME)

$(NAME): $(OBJECTS)
	$(CC) $(CFLAGS) $(OBJECTS) -o $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJECTS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re test