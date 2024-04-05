CC = gcc
CFLAGS = -Wall -g
NOME = transporte
OBJS = libAux.o transporte.o
all: $(OBJS)
	$(CC) $(OBJS) -o $(NOME)

transporte.o: transporte.c libAux.h
	$(CC) $(CFLAGS) -c transporte.c

libAux.o: libAux.c libAux.h
	$(CC) $(CFLAGS) -c libAux.c

clean:
	rm -f *.o

purge: clean
	rm -f *~ $(NOME)