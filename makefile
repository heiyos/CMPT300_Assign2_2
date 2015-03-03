CFLAGS=-pthread
CC=gcc $(CFLAGS)
OBJECTS=sync.o main.o

mylocks: $(OBJECTS) 
	$(CC) $(OBJECTS) -o mylocks
clean:
	rm -f mylocks main.o sync.o
run: mylocks
	./mylocks
