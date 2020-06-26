# definition des commandes utilisées
CC = gcc
# d ́eclaration des options pour gcc
CFLAGS =
CPPFLAGS = -I.
# definition des fichiers et dossiers
PROG = uno
HEADERS = head.h
SRC=game.c main.c
OBJS = $(SRC:.c=.o)

all:	$(PROG)

$(PROG):	$(OBJS)
	$(CC) $^ -o $(PROG)
%.o: %.c $(HEADERS)
	$(CC) $(CPPFLAGS) $(CFLAGS) -c $<
