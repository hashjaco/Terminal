CC=gcc
CFLAGS= -I -Wall
DEPS = shellcommands.h
OBJ = shellcommands.o myshell2.o

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

myshell: $(OBJ)
	 $(CC) -o $@ $^ $(CFLAGS)

clean:
	rm myshell
	
