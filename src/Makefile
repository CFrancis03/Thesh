CC = gcc
CFLAGS = -Wall -g
DEPS = thesh.h
OBJ = main.o builtins.o input.o execute.o

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

thesh: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)

clean:
	rm -f *.o thesh

