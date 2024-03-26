CC = gcc
CFLAGS = -Wall -g
NOME = transporte

all: $(NOME)

programa:
	$(CC) $(CFLAGS) $(NOME).c -o $(NOME)

clean:
	rm -f *.o

purge: clean
	rm -f *~ $(NOME)