CC=gcc
CFLAGS=-I.
DEPS = scanner.h keywords.h parser.c interpreter.c expression.c

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

Knudon: driver.c 
	$(CC) -o Knudon driver.c
