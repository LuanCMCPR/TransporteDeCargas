CC = gcc
CFLAGS = -Wall -g
NOME = transporte
TEAM = lcmc20-lmmm20
OBJS = libAux.o transporte.o
DIR = fontes/
all: $(OBJS)
	$(CC) $(OBJS) -o $(NOME)

transporte.o: $(DIR)transporte.c $(DIR)libAux.h
	$(CC) $(CFLAGS) -c $(DIR)transporte.c

libAux.o: $(DIR)libAux.c $(DIR)libAux.h
	$(CC) $(CFLAGS) -c $(DIR)libAux.c

compact:
	tar -cvzf $(TEAM).tar.gz fontes exemplos makefile

clean:
	rm -f *.o 

purge: clean
	rm -f *~ $(NOME) $(TEAM).tar.gz